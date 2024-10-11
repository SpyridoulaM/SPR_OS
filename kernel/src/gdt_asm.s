global gdt_flush

gdt_flush:
    mov eax, [esp + 4]  ; Load the GDT pointer
    lgdt [eax]          ; Load the GDT
    mov ax, 0x10        ; Offset for the data segment
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax
    jmp 0x08:.flush     ; Long jump to the code segment
.flush:
    ret