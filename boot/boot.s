; Multiboot header constants
%define ALIGN     (1 << 0)            ; Align loaded modules on page boundaries
%define MEMINFO   (1 << 1)            ; Provide memory map
%define FLAGS     (ALIGN | MEMINFO)   ; Multiboot 'flag' field
%define MAGIC     0x1BADB002          ; Multiboot magic number
%define CHECKSUM  -(MAGIC + FLAGS)    ; Checksum of header

section .multiboot
align 4
dd MAGIC
dd FLAGS
dd CHECKSUM

; Declare kernel_main as external
extern kernel_main

; Reserve 16 KiB stack space
section .bss
align 16
stack_bottom:
    resb 16384    ; Allocate 16 KiB for the stack
stack_top:

section .text
global _start

_start:
    ; Set up stack
    mov esp, stack_top

    ; Call the C kernel
    call kernel_main

    ; Infinite loop (halt the CPU)
    cli
halt:
    hlt
    jmp halt
