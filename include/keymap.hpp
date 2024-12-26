#pragma once

#include <core/port.h>
#include <common/types.h>
#include <system/log.h>


#define KEYBOARD_DATA_PORT 0x60
#define KEYBOARD_STATUS_PORT 0x64
#define KEYBOARD_BUFFER_SIZE 256

// Scancode to ASCII table (simplified)
static char scancode_to_ascii[128] = {
    0, 27, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', '\b',
    '\t', 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n', 0,
    'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`', 0, '\\', 'z',
    'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/', 0, '*', 0, ' ', 0
};

// Keyboard buffer
static char keyboard_buffer[KEYBOARD_BUFFER_SIZE];
static uint8_t buffer_index = 0;

// IDT Entry Structure
struct IDT_Entry {
    uint16_t offset_low;
    uint16_t selector;
    uint8_t zero;
    uint8_t type_attr;
    uint16_t offset_high;
} __attribute__((packed));

// IDT Descriptor Structure
struct IDTDescriptor {
    uint16_t limit;
    uint32_t base;
} __attribute__((packed));

// IDT Table
static IDT_Entry idt[256];

// Keyboard interrupt handler function
void keyboard_interrupt_handler() {
    uint8_t scancode = Novanix::core::inportb(KEYBOARD_DATA_PORT);
    if (scancode < sizeof(scancode_to_ascii)) {
        char key = scancode_to_ascii[scancode];
        if (key) {
            if (key == '\n') {
                printk(VGA_COLOR_GREEN, "\n");
            } else {
                if (buffer_index < KEYBOARD_BUFFER_SIZE - 1) {
                    keyboard_buffer[buffer_index++] = key;
                    keyboard_buffer[buffer_index] = '\0';
                }
                printk(VGA_COLOR_GREEN, "%c", key);
            }
        }
    }
    // Send EOI
    Novanix::core::outportb(0x20, 0x20);
}

// Unified setup function
void setup_interrupts_and_keyboard() {
    // Install IDT entries
    // for (int i = 0; i < 256; i++) {
    //     idt[i].offset_low = 0;
    //     idt[i].selector = 0x08; // Kernel code segment
    //     idt[i].zero = 0;
    //     idt[i].type_attr = 0x8E; // Interrupt gate
    //     idt[i].offset_high = 0;
    // }

    // // Set keyboard interrupt (IRQ1 = Interrupt 33)
    // uint32_t handler_address = reinterpret_cast<uint32_t>(&keyboard_interrupt_handler);

    // idt[33].offset_low = handler_address & 0xFFFF;
    // idt[33].selector = 0x08;
    // idt[33].zero = 0;
    // idt[33].type_attr = 0x8E;
    // idt[33].offset_high = (handler_address >> 16) & 0xFFFF;

    // // Load IDT
    // IDTDescriptor idt_descriptor;
    // idt_descriptor.limit = sizeof(idt) - 1;
    // idt_descriptor.base = (uint32_t)&idt;
    // asm volatile("lidt (%0)" : : "r"(&idt_descriptor));

    // // Unmask IRQ1 (keyboard)
    // uint8_t mask = Novanix::core::inportb(0x21);
    // mask &= ~(1 << 1); // Clear the bit for IRQ1
    // Novanix::core::outportb(0x21, mask);

    // Enable interrupts
    // asm volatile("sti");
}