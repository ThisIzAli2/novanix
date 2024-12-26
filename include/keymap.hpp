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
        case 154:
        case 26:
        return "{";
        case 155:
        case 27:
        return "}";
        


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
