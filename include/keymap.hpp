#pragma once

#define KEYBOARD_DATA_PORT 0x60
#define KEYBOARD_STATUS_PORT 0x64

#include <stringify.h>
#include <system/log.h>
#include <typing.hpp>
bool shift = false;


#define DEV
// Function to read a byte from the keyboard data port

// Inline assembly function to read from I/O port
inline uint8_t inb(uint16_t port) {
    uint8_t result;
    asm volatile ("inb %1, %0" : "=a"(result) : "dN"(port));
    return result;
}

uint8_t read_key() {
    uint8_t scan_code;

    // Wait until the keyboard controller is ready to send data
    while ((inb(KEYBOARD_STATUS_PORT) & 0x01) == 0);

    // Read the scan code from the data port
    scan_code = inb(KEYBOARD_DATA_PORT);

    return scan_code;
}

inline char* handle_keyboard(uint8_t scan_code){
    int count = 0;
    switch(scan_code){
        case 144:
        case 16:
            return "q";
        case 145:
        case 17:
            return "w";
        case 146:
        case 18:
        return "e";
        case 147:
        case 19:
        return "r";
        case 148:
        case 20:
        return "t";
        case 149:
        case 21:
        return "y";
        case 150:
        case 22:
        return "u";
        case 154:
        case 26:
        return "{";
        case 155:
        case 27:
        return "}";
        case 186:
        case 30:
        return "a";
        case 159:
        case 31:
        return "s";
        case 160:
        case 32:
        return "d";
        case 161:
        case 33:
        return "f";
        case 162:
        case 34:
        return "g";
        case 163:
        case 35:
        return "h";
        case 164:
        case 36:
        return "j";
        case 165:
        case 37:
        return "k";
        case 166:
        case 38:
        return "l";
        case 167:
        case 39:
        return ";";
        case 44:
        case 172:
        return "z";
        case 173:
        case 45:
        return "x";
        case 174:
        case 46:
        return "c";
        case 175:
        case 47:
        return "v";
        case 176:
        case 48:
        return "b";
        case 177:
        case 49:
        return "n";
        case 178:
        case 50:
        return "m";
        case 179:
        case 51:
        return ",";
        case 152:
        case 24:
        return "o";
        case 156:
        return "\n";
        case 185:
        return " ";
        case 143:
        return "    ";
        case 130:
        return "1";
        case 131:
        return "2";
        case 132:
        return "3";
        case 133:
        return "4";
        case 134:
        return "5";
        case 135:
        return "6";
        case 136:
        return "7";
        case 137:
        return "8";
        case 138:
        return "9";
        case 139:
        return "0";
        case 140:
        return "-";
        case 141:
        return "=";
        case 169:
        return "~";
        case 28:
        return "\n";
        case 57:
        return " ";
        case 2:
        if (shift){
            return "!";
        }
        return "1";
        case 3:
        return "2";
        case 4:
        return "3";
        case 5:
        return "4";
        case 6:
        return "5";
        case 7:
        return "6";
        case 8:
        return "7";
        case 9:
        return "8";
        case 10:
        return "9";
        case 11:
        return "0";
        case 12:
        return "-";
        case 15:
        return "    ";
        case 23:
        return "i";
        case 151:
        return "i";
        case 158:
        return "a";
        case 25:
        case 153:
        return "p";
        case 14:
        case 142:
        return "\b";
        case 244:
        return "left";
        case 42:
        case 54:
        if (count == 1){
            shift = false;
            count = 0;
        }
        shift = true;
        count = 1;
        // case 58:
        // return "caps";


        #ifdef DEV
        
        default:
        return stringify(scan_code);
        
        #endif
        
        // default:
        // int code = (sca)
            // return system::printk(VGA_COLOR_WHITE,(scan_code)(int),1);

    }
}

// Interrupt handler for keyboard interrupt (IRQ1)
extern "C" VOID keyboard_interrupt_handler() {
    uint8_t key = read_key();

    // Process the key here (e.g., store it, display it, etc.)
    // For example, you can print the key to the screen or handle it accordingly.
    // This part depends on your kernel's design.

    // Acknowledge the interrupt (this is typically done by sending a signal to the PIC)
    // send_eoi(IRQ1);
}
