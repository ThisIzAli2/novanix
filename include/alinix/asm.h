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
 * @file asm.h
 * @abstraction:
 *  - Kernel ASM implemented.
*/
#ifndef __ALINIX_KERNEL_ASM_H
#define __ALINIX_KERNEL_ASM_H

# define RET    bx      lr

/**
 * @brief outing the data to specific port.
*/
#define outb(_port, _data)  \
    asm volatile("outb %b0, %w1" \
        : \
        : "a" (_data), "Nd" (_port) \
    );

#define PAUSE asm("pause")



// Macros for signal stuff
#define PIC1		0x20		/* IO base address for master PIC */
#define PIC2		0xA0		/* IO base address for slave PIC */
#define PIC1_COMMAND	PIC1
#define PIC1_DATA	(PIC1+1)
#define PIC2_COMMAND	PIC2
#define PIC2_DATA	(PIC2+1)

#endif /*__ALINIX_KERNEL_ASM_H*/