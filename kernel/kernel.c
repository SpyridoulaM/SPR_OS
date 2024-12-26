#include <stdint.h>
#include <stddef.h>
#include "src/vga.h"
#include "src/gdt.h"
#include "src/idt.h"
#include "src/utils.h"
#include "src/pit.h"
#include "drivers/keyboard.h"

void kernel_main()
{
    clear_screen();
    set_term_color(VGA_COLOR_WHITE);
    prints("Welcome to the kernel.\n");
    
    initGdt();
    prints_color("GDT set up.\n", VGA_COLOR_GREEN);

    initIdt();
    prints_color("IDT set up.\n", VGA_COLOR_GREEN);

    initTimer();
    prints_color("Timer set up.\n", VGA_COLOR_GREEN);

    initKeyboard();
    prints_color("Keyboard set up.\n", VGA_COLOR_GREEN);
    for (;;);
    
}
