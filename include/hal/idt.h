/**
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


#ifndef IDT_H
#define IDT_H


#include <types.h>


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

void idt_init(uint16_t code);
void default_ir_handler();
void install_ir(uint32_t i, uint16_t flags, uint16_t sel, void *irq);
extern void idt_set(struct idt_ptr *ptr);
extern void gen_int(uint32_t code);




#endif // IDT_H