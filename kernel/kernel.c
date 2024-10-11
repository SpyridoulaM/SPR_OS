#include <stdint.h>
#include <stddef.h>
#include "libs/vga.h"
#include "gdt/gdt.h"
#include "idt/idt.h"

void kernel_main()
{
    clear_screen();
    set_term_color(VGA_COLOR_WHITE);
    prints("Welcome to the kernel.\n");
    
    initGdt();
    prints_color("GDT is done.\n", VGA_COLOR_GREEN);

    i686_IDT_Initialize();
    prints_color("IDT is done.\n", VGA_COLOR_GREEN);
}
