/**
 * @author Ali Mirmohammad
 ** This file is part of AliNix.

**AliNix is free software: you can redistribute it and/or modify
**it under the terms of the GNU Affero General Public License as published by
**the Free Software Foundation, either version 3 of the License, or
**(at your option) any later version.

**AliNix is distributed in the hope that it will be useful,
**but WITHOUT ANY WARRANTY; without even the implied warranty of
**MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
**GNU Affero General Public License for more details.

**You should have received a copy of the GNU Affero General Public License
**along with AliNix. If not, see <https://www.gnu.org/licenses/>.
*/

/**
 * @file idt.h
 * @abstract:
 *  - Kernel IDT implementation.
*/
#ifndef __ALINIX_KERNEL_IDT_H
#define __ALINIX_KERNEL_IDT_H

#include <alinix/types.h>

#define IDT_ENTRY_SIZE 256
#define IDT_PRESENT 0x80
#define IDT_INTERRUPT 0xE
#define IDT_INTERRUPT_OFFSET 0x20


/**
 * @brief IDT data structure.
*/
struct IDTEntry
{
    uint16_t handlerLowBits;
    uint16_t selector;
    uint8_t reserved;
    uint8_t access;
    uint16_t handlerHighBits;
} __attribute__((packed));


/**
 * @brief IDT pointer data structure.
*/
struct IDTPointer
{
    uint16_t size;
    uint32_t base;
} __attribute__((packed));


/**
 * @brief All Interrupt implemented for kernel to be handled.
*/
void IgnoreInterrupt();
void HandleInterruptRequest0x00();
void HandleInterruptRequest0x01();
void HandleInterruptRequest0x02();
void HandleInterruptRequest0x03();
void HandleInterruptRequest0x04();
void HandleInterruptRequest0x05();
void HandleInterruptRequest0x06();
void HandleInterruptRequest0x07();
void HandleInterruptRequest0x08();
void HandleInterruptRequest0x09();
void HandleInterruptRequest0x0A();
void HandleInterruptRequest0x0B();
void HandleInterruptRequest0x0C();
void HandleInterruptRequest0x0D();
void HandleInterruptRequest0x0E();
void HandleInterruptRequest0x0F();
void HandleInterruptRequest0x31();

void HandleInterruptRequest0xDD();
void HandleInterruptRequest0x60();

void HandleException0x00();
void HandleException0x01();
void HandleException0x02();
void HandleException0x03();
void HandleException0x04();
void HandleException0x05();
void HandleException0x06();
void HandleException0x07();
void HandleException0x08();
void HandleException0x09();
void HandleException0x0A();
void HandleException0x0B();
void HandleException0x0C();
void HandleException0x0D();
void HandleException0x0E();
void HandleException0x0F();
void HandleException0x10();
void HandleException0x11();
void HandleException0x12();
void HandleException0x13();

void IdtSetDescriptor(uint32_t number,  void (*handler)(), int accesLevel);

uint32_t HandleInterrupt(struct CPUState* state);
void Install();

void EnableInterrupts();
void DisableInterrupts();
bool AreEnabled();

#define MAX_INTERRUPTS 256


struct idt_info{
    uint16_t base_low;
    uint16_t sel;
    uint8_t reserved;
    uint8_t flags;
    uint16_t base_high;
}__attribute__((__packed__));


struct idt_ptr {
    uint16_t limit;
    uint32_t base;
} __attribute__((__packed__));

void install_ir(uint32_t i, uint16_t flags, uint16_t sel, void *irq);
#endif /*__ALINIX_KERNEL_IDT_H*/