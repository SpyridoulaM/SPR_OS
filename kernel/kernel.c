#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include "libs/vga.h"

void kernel_main()
{
    clear_screen();
    set_term_color(VGA_COLOR_WHITE);
    prints("Welcome to the kernel.\n");
    
    prints_color("TEST1.\n", VGA_COLOR_GREEN);
    prints("TEST2.\n");
}
