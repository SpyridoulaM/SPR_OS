#include <stdint.h>
#include "../src/idt.h"
#include "../src/utils.h"
#include "../src/vga.h"
#include "keyboard.h"

uint8_t capsOn;
uint8_t capsLock;

const uint32_t UNKNOWN = 0xFFFFFFFF;
const uint32_t ESC = 0xFFFFFFFF - 1;
const uint32_t CTRL = 0xFFFFFFFF - 2;
const uint32_t LSHFT = 0xFFFFFFFF - 3;
const uint32_t RSHFT = 0xFFFFFFFF - 4;
const uint32_t ALT = 0xFFFFFFFF - 5;
const uint32_t F1 = 0xFFFFFFFF - 6;
const uint32_t F2 = 0xFFFFFFFF - 7;
const uint32_t F3 = 0xFFFFFFFF - 8;
const uint32_t F4 = 0xFFFFFFFF - 9;
const uint32_t F5 = 0xFFFFFFFF - 10;
const uint32_t F6 = 0xFFFFFFFF - 11;
const uint32_t F7 = 0xFFFFFFFF - 12;
const uint32_t F8 = 0xFFFFFFFF - 13;
const uint32_t F9 = 0xFFFFFFFF - 14;
const uint32_t F10 = 0xFFFFFFFF - 15;
const uint32_t F11 = 0xFFFFFFFF - 16;
const uint32_t F12 = 0xFFFFFFFF - 17;
const uint32_t SCRLCK = 0xFFFFFFFF - 18;
const uint32_t HOME = 0xFFFFFFFF - 19;
const uint32_t UP = 0xFFFFFFFF - 20;
const uint32_t LEFT = 0xFFFFFFFF - 21;
const uint32_t RIGHT = 0xFFFFFFFF - 22;
const uint32_t DOWN = 0xFFFFFFFF - 23;
const uint32_t PGUP = 0xFFFFFFFF - 24;
const uint32_t PGDOWN = 0xFFFFFFFF - 25;
const uint32_t END = 0xFFFFFFFF - 26;
const uint32_t INS = 0xFFFFFFFF - 27;
const uint32_t DEL = 0xFFFFFFFF - 28;
const uint32_t CAPS = 0xFFFFFFFF - 29;
const uint32_t NONE = 0xFFFFFFFF - 30;
const uint32_t ALTGR = 0xFFFFFFFF - 31;
const uint32_t NUMLCK = 0xFFFFFFFF - 32;


const uint32_t lowercase[128] = {
UNKNOWN,ESC,'1','2','3','4','5','6','7','8',
'9','0','-','=','\b','\t','q','w','e','r',
't','y','u','i','o','p','[',']','\n',CTRL,
'a','s','d','f','g','h','j','k','l',';',
'\'','`',LSHFT,'\\','z','x','c','v','b','n','m',',',
'.','/',RSHFT,'*',ALT,' ',CAPS,F1,F2,F3,F4,F5,F6,F7,F8,F9,F10,NUMLCK,SCRLCK,HOME,UP,PGUP,'-',LEFT,UNKNOWN,RIGHT,
'+',END,DOWN,PGDOWN,INS,DEL,UNKNOWN,UNKNOWN,UNKNOWN,F11,F12,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,
UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,
UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,
UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN
};

const uint32_t uppercase[128] = {
    UNKNOWN,ESC,'!','@','#','$','%','^','&','*','(',')','_','+','\b','\t','Q','W','E','R',
'T','Y','U','I','O','P','{','}','\n',CTRL,'A','S','D','F','G','H','J','K','L',':','"','~',LSHFT,'|','Z','X','C',
'V','B','N','M','<','>','?',RSHFT,'*',ALT,' ',CAPS,F1,F2,F3,F4,F5,F6,F7,F8,F9,F10,NUMLCK,SCRLCK,HOME,UP,PGUP,'-',
LEFT,UNKNOWN,RIGHT,'+',END,DOWN,PGDOWN,INS,DEL,UNKNOWN,UNKNOWN,UNKNOWN,F11,F12,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,
UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,
UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,
UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN
};

void initKeyboard() {
    capsOn = 0;
    capsLock = 0;

    irq_install_handler(1, &keyboardHandler);
}

void keyboardHandler(struct InterruptRegisters *regs) {
    uint8_t scanCode = inPortB(0x60) & 0x7F; // Get scan code
    uint8_t press = inPortB(0x60) & 0x80;    // Get press/release status

    // Handle special keys
    if (press == 0) {
        switch (scanCode) {
            case 1:
                prints("ESC\n");
                break;
            case 29:
                prints("CTRL\n");
                break;
            case 56:
                prints("ALT\n");
                break;
            case 42:
            case 54:
                prints("Shift\n");
                capsOn = 1; // Handle shift key
                break;
            case 58:
                if (!capsLock) {
                    capsLock = 1;
                    prints("CapsLock ON\n");
                } else {
                    capsLock = 0;
                    prints("CapsLock OFF\n");
                }
                break;
            default:
                // Handle printable characters
                char keyString[2]; // Buffer to hold the character and a null terminator
                keyString[1] = '\0'; // Null-terminate the string

                if (capsOn || capsLock) {
                    // For uppercase letters or caps lock
                    keyString[0] = (char)uppercase[scanCode];
                } else {
                    // For lowercase letters
                    keyString[0] = (char)lowercase[scanCode];
                }
                // Print the character string
                prints(keyString);
                prints("\n");
                break;
        }
    }
}

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