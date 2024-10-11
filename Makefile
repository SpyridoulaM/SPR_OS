# Define the toolchain
CC = i686-elf-gcc
AS = nasm
LD = i686-elf-ld

# Define the target binary
TARGET = SPR_OS.bin

# Define the source files
ASM_SOURCES = boot/boot.s kernel/src/gdt_asm.s kernel/src/idt_asm.s
C_SOURCES = kernel/kernel.c kernel/src/vga.c kernel/src/gdt.c kernel/src/idt.c kernel/src/utils.c
OBJECTS = $(ASM_SOURCES:.s=.o) $(C_SOURCES:.c=.o)

# Define compilation flags
CFLAGS = -m32 -ffreestanding -c
ASFLAGS = -f elf32                 # NASM flag to generate 32-bit ELF output
LDFLAGS = -T linker.ld

# Create the ISO output directory if it doesn't exist
ISO_DIR = isodir
BOOT_DIR = $(ISO_DIR)/boot

.PHONY: all iso run clean

# Define rules
all: $(TARGET)

# Linking the kernel
$(TARGET): $(OBJECTS)
	$(LD) $(LDFLAGS) -o $@ $(OBJECTS)

# Compile assembly source files with NASM
%.o: %.s
	$(AS) $(ASFLAGS) $< -o $@

# Compile C source files
%.o: %.c
	$(CC) $(CFLAGS) $< -o $@

# Clean up generated files
clean:
	rm -f $(OBJECTS) $(TARGET)

# Create ISO directory and build ISO
iso: $(TARGET)
	@mkdir -p $(BOOT_DIR)/grub  # Create the grub directory
	cp $(TARGET) $(BOOT_DIR)/SPR_OS.bin
	echo 'menuentry "SPR_OS" { multiboot /boot/SPR_OS.bin; boot }' > $(BOOT_DIR)/grub/grub.cfg
	grub-mkrescue -o SPR_OS.iso $(ISO_DIR)

# Run the kernel in QEMU
run: iso
	qemu-system-i386 -cdrom SPR_OS.iso &

# Combined target for building, ISO creation, running, and cleaning
rc: all iso run clean
