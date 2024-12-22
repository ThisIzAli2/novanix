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
 * @file fpu.h
 * Purpose:
 *      - Fpu  support class for x86 architecture.
*/
#ifndef __ALINIX_KERNEL_FPU_H
#define __ALINIX_KERNEL_FPU_H

#include <alinix/types.h>


/**
 * @brief FPU util data structure.
*/
struct FPUControlWord
{
    uint8_t InvalidOperand : 1;
    uint8_t DenormalOperand : 1;
    uint8_t ZeroDevide : 1;
    uint8_t Overflow : 1;
    uint8_t Underflow : 1;
    uint8_t Precision : 1;
    uint8_t reserved1 : 1;
    uint8_t reserved2 : 1;
    uint8_t PrecisionControl : 2;
    uint8_t RoundingControl : 2;
    uint8_t InfinityControl : 1;
    uint8_t reserved3 : 3;
} __attribute__((packed));

static void Enable();

/**
 * @brief
 *  - Used to load a new value to FPU.
*/
inline void fpu_load_control_word(const uint16_t control){
    asm volatile("fldcw %0;"::"m"(control)); 
}

#endif /*__ALINIX_KERNEL_FPU_H*/