#include <stdint.h>
#include "../src/idt.h"
#include "../src/utils.h"
#include "../src/vga.h"
#include "keyboard.h"

// Function to convert scan code to int
int ScanCodeToInt(uint8_t scanCode) {
    return (int)scanCode; // Cast the uint8_t scanCode to int and return
}

// Function to print the scan code as an integer
void printScanCode(uint8_t scanCode) {
    prints("Scan code: ");
    int num = ScanCodeToInt(scanCode); // Get the integer value of the scan code

    // Convert the integer to a decimal string for printing
    char decString[4];  // Buffer for the decimal representation (3 digits + null terminator)
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

// Initialize the keyboard
void initKeyboard() {
    irq_install_handler(1, &keyboardHandler);
}

// Keyboard interrupt handler
void keyboardHandler(struct InterruptRegisters *regs) {
    uint8_t scanCode = inPortB(0x60) & 0x7F; // Get scan code
    uint8_t press = inPortB(0x60) & 0x80;    // Get press/release status

    printScanCode(scanCode); // Print the scan code in decimal

    // Print press/release status
    if (press == 0) {
        prints(": Pressed\n");
    } else {
        prints(": Released\n");
    }
}
