#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include "libs/vga.h"
#include "gdt/gdt.h"

void kernel_main()
{
    clear_screen();
    set_term_color(VGA_COLOR_WHITE);
    prints("Welcome to the kernel.\n");
    
    initGdt();
    prints_color("GDT is done.\n", VGA_COLOR_GREEN);
}
