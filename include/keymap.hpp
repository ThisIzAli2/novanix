#pragma once

#define KEYBOARD_DATA_PORT 0x60
#define KEYBOARD_STATUS_PORT 0x64

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
            case 151:
            case 23:
            return "i";
            case 152:
            case 24:
            return "o";
            case 153:
            case 25:
            return "p";
            case 154:
            case 26:
            return "a";
            case 155:
            case 27:
            return "s";
            case 156:
            case 28:
            return "d";
            case 157:
            case 29:
            return "f";
            case 158:
            case 30:
            return "g";
            case 159:
            case 31:
            return "h";
            case 160:
            case 32:
            return "j";
            case 161:
            case 33:
            return "k";
            case 162:
            case 34:
            return "l";
            case 163:
            case 35:
            return "z";
            case 164:
            case 36:
            return "x";
            case 165:
            case 37:
            return "c";
            case 166:
            case 38:
            return "v";
            case 167:
            case 39:
            return "b";
            case 168:
            case 40:
            return "n";
            case 169:
            case 41:
            return "m";
            case 170:
            case 42:
            return ",";
            case 171:
            case 43:
            return ".";
            case 172:
            case 44:
            return "/";
            case 173:
            case 45:
            return " ";
            case 174:
            case 46:
            return "0";
            case 175:
            case 47:
            return "1";
            case 176:
            case 48:
            return "2";
            case 177:
            case 49:
            return "3";
            case 178:
            case 50:
            return "4";
            case 179:
            case 51:
            return "5";
            case 180:
            case 52:
            return "6";
            case 181:
            case 53:
            return "7";
            case 182:
            case 54:
            return "8";
            case 183:
            case 55:
            return "9";
            case 184:
            case 56:
            return "a";
            case 185:
            case 57:
            return "b";
            case 186:
            case 58:
            return "c";

    }
}

// Interrupt handler for keyboard interrupt (IRQ1)
extern "C" void keyboard_interrupt_handler() {
    uint8_t key = read_key();

    // Process the key here (e.g., store it, display it, etc.)
    // For example, you can print the key to the screen or handle it accordingly.
    // This part depends on your kernel's design.

    // Acknowledge the interrupt (this is typically done by sending a signal to the PIC)
    // send_eoi(IRQ1);
}
