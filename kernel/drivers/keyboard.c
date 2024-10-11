#include <stdint.h>
#include "../src/idt.h"
#include "../src/utils.h"
#include "../src/vga.h"
#include "keyboard.h"

void initKeyboard()
{
    irq_install_handler(1,&keyboardHandler);
}

void keyboardHandler(struct InterruptRegisters *regs)
{
    char scanCode=inPortB(0x60)&0x7F; //scan code of the key pressed
    char press=inPortB(0x60)&0x80; //if the key is pressed down or released

    prints("Scan code:");
    char scanCodeStr[5];  // Buffer to hold the scan code string
    itoa(scanCode, scanCodeStr, 16);  // Convert scan code to hexadecimal
    prints(scanCodeStr); 

    prints(",Press:");
    char pressStr[5];  // Buffer to hold the press state string
    itoa(press, pressStr, 16);  // Convert press state to hexadecimal
    prints(pressStr); 
    
    prints("\n");
}