#include <stdint.h>
#include "../src/idt.h"
#include "../src/utils.h"
#include "../src/vga.h"
#include "keyboard.h"

// Simple function to print scan code in decimal format
void printScanCode(uint8_t scanCode) {
    prints("Scan code: ");
    char decString[4];  // Buffer for the decimal representation (3 digits + null)
    // Convert scan code to decimal manually
    int num = scanCode;
    int i = 0;
    // Handle 0 explicitly
    if (num == 0) {
        decString[i++] = '0';
    } else {
        // Convert the number to decimal string
        while (num > 0) {
            decString[i++] = (num % 10) + '0'; // Get last digit and convert to char
            num /= 10; // Reduce number
        }
    }
    // Null-terminate the string
    decString[i] = '\0';
    // Reverse the string to get the correct order
    for (int j = 0; j < i / 2; j++) {
        char temp = decString[j];
        decString[j] = decString[i - j - 1];
        decString[i - j - 1] = temp;
    }
    // Print the decimal string
    prints(decString);
}

void initKeyboard() {
    irq_install_handler(1, &keyboardHandler);
}

void keyboardHandler(struct InterruptRegisters *regs) {
    uint8_t scanCode = inPortB(0x60) & 0x7F; // Get scan code
    uint8_t press = inPortB(0x60) & 0x80;    // Get press/release status

    printScanCode(scanCode); // Print the scan code in decimal

    // Print press/release status
    if (press == 0) {
        prints(":Pressed\n");
    } else {
        prints(":Released\n");
    }
}
