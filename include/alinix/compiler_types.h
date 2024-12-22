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
 * @file compiler_types.h
 * Purpose:
 *      -Defines the compiler types  supported by AliNix.
*/
#ifndef __ALINIX_KERNEL_COMPILER_TYPES_H
#define __ALINIX_KERNEL_COMPILER_TYPES_H

#define __naked			__attribute__((__naked__)) notrace
#define __naked __attribute__((naked))
#define __clobber_all "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "memory"
#define __clobber_common "r0", "r1", "r2", "r3", "r4", "r5", "memory"
# define __force	__attribute__((force))

#if defined(_M_IX86)
__naked void unreachable(void)
{
	asm volatile ("					\
	exit;						\
	exit;						\
"	::: __clobber_all);
}
#elif defined(_M_ARM64)
__attribute__((naked)) void unreachable(void) {
    asm volatile (
        "mov x0, #93\n"   // __NR_exit
        "mov x1, #0\n"    // status = 0
        "svc #0\n"        // exit(0)
        "b .\n"           // infinite loop to ensure function does not return
    );
}

#else 
// __attribute__((naked)) void __unreachable(void) {

// }

# define __randomize_layout __attribute__((randomize_layout))


#endif

#endif /*__ALINIX_KERNEL_COMPILER_TYPES_H*/
