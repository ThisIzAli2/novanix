/**
 * @author Ali Mirmohammad
 * @file isr.h
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
 * @abstract:
 *  - Kernel ISR header file implemented.
*/
#ifndef __ALINIX_KERNEL_ISR_H
#define __ALINIX_KERNEL_ISR_H

#include <alinix/types.h>

// IRQ default constants
#define IRQ_BASE            0x20
#define IRQ0_TIMER          0x00
#define IRQ1_KEYBOARD       0x01
#define IRQ2_CASCADE        0x02
#define IRQ3_SERIAL_PORT2   0x03
#define IRQ4_SERIAL_PORT1   0x04
#define IRQ5_RESERVED       0x05
#define IRQ6_DISKETTE_DRIVE 0x06
#define IRQ7_PARALLEL_PORT  0x07
#define IRQ8_CMOS_CLOCK     0x08
#define IRQ9_CGA            0x09
#define IRQ10_RESERVED      0x0A
#define IRQ11_RESERVED      0x0B
#define IRQ12_AUXILIARY     0x0C
#define IRQ13_FPU           0x0D
#define IRQ14_HARD_DISK     0x0E
#define IRQ15_RESERVED      0x0F



/**
 * @brief ISR CPU registers structure data type.
*/
typedef struct {
    uint32_t ds;
    uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax;  // pushed by pusha
    uint32_t int_no, err_code;                        // interrupt number and error code
    uint32_t eip, cs, eflags, useresp, ss;            // pushed by the processor automatically
} REGISTERS;


/**
 * @brief ISR CPU registers structure data type.
*/

typedef struct {
    uint16_t di;
    uint16_t si;
    uint16_t bp;
    uint16_t sp;
    uint16_t bx;
    uint16_t dx;
    uint16_t cx;
    uint16_t ax;
    // segments
    uint16_t ds;
    uint16_t es;
    uint16_t fs;
    uint16_t gs;
    uint16_t ss;
    uint16_t eflags;
} REGISTERS16;

// ISR function prototype
typedef void (*ISR)(REGISTERS *);

#endif // __ALINIX_KERNEL_ISR_H