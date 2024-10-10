ENTRY(_start)

SECTIONS
{
    /* Load the kernel at the 1MB mark */
    . = 0x100000;

    /* Multiboot header section */
    .multiboot : {
        *(.multiboot)
    }

    /* Code (.text section) */
    .text : {
        *(.text)
    }

    /* Read-only data (.rodata section) */
    .rodata : {
        *(.rodata)
    }

    /* Data (.data section) */
    .data : {
        *(.data)
    }

    /* Uninitialized data (.bss section) */
    .bss : {
        *(.bss)
    }

    /* Stack */
    . = ALIGN(4);
    stack_top = . + 0x1000;  /* Stack size (4KB) */
    .stack (NOLOAD) : {
        *(.stack)
    }
}

