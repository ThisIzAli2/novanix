/**
 * @author Ali Mirmohammad
 * @file assembly.h
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
 * @abstraction:
 *  - Kernel asm util.
*/
#ifndef __ALINIX_KERNEL_ASSEMBLY_H
#define __ALINIX_KERNEL_ASSEMBLY_H

#define Nop() asm("nop")		//Null instruction

#define	INSTRUCTION_CLOCK_FREQUENCY	80000000

#define __print_asm(msg) \
    asm volatile ( \
        "mov $0x0E, %%ah \n"   /* Set AH to 0x0E (Teletype output) */ \
        "1: lodsb \n"           /* Load next byte from string into AL */ \
        "cmp $0, %%al \n"       /* Check for null terminator */ \
        "je 2f \n"              /* If null terminator, jump to end */ \
        "int $0x10 \n"          /* Otherwise, call BIOS interrupt for screen output */ \
        "jmp 1b \n"             /* Repeat loop */ \
        "2: \n"                 /* End label */ \
        :                       /* Output operands (none) */ \
        : "S"(msg)              /* Input operand (address of string) */ \
        : "ah", "al"            /* Clobbered registers */ \
    )


#endif // __ALINIX_KERNEL_ASSEMBLY_H