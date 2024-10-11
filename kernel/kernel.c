#include <stdint.h>
#include <stddef.h>
#include "src/vga.h"
#include "src/gdt.h"
#include "src/idt.h"
#include "src/utils.h"

void kernel_main()
{
    clear_screen();
    set_term_color(VGA_COLOR_WHITE);
    prints("Welcome to the kernel.\n");
    
    initGdt();
    prints_color("GDT is done.\n", VGA_COLOR_GREEN);

    initIdt();
    prints_color("IDT is done.\n", VGA_COLOR_GREEN);
}
