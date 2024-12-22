/**
 * @file bitops.h
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
 * 	- Bit operations in header file.
*/
#ifndef _____BITOPS_H
#define _____BITOPS_H

#include <alinix/types.h>

#define BITS_PER_LONG 32

#define _IOMMU_TEST_CMD(x) IOMMU_TEST_CMD
# define __BITS_PER_LONG 32
/* Imported from include/asm-generic/bitops/generic-non-atomic.h */
#define BITS_PER_BYTE 8
#define BITS_PER_LONG __BITS_PER_LONG
#define BIT_MASK(nr) (1UL << ((nr) % __BITS_PER_LONG))
#define BIT_WORD(nr) ((nr) / __BITS_PER_LONG)


/**
 * set_bit - Set a bit in memory
 * @nr: the bit to set
 * @addr: the address of the memory location to change
 *
 * Set the bit at position @nr in the memory pointed to by @addr. This function
 * uses inline assembly to perform an atomic bit set operation. It reads the
 * current value from memory, sets the specified bit, and writes the new value
 * back to memory atomically.
 */
static inline void
set_bit(unsigned long nr, volatile void * addr)
{
	unsigned long temp;
	int *m = ((int *) addr) + (nr >> 5);

	__asm__ __volatile__(
	"1:	ldl_l %0,%3\n"
	"	bis %0,%2,%0\n"
	"	stl_c %0,%1\n"
	"	beq %0,2f\n"
	".subsection 2\n"
	"2:	br 1b\n"
	".previous"
	:"=&r" (temp), "=m" (*m)
	:"Ir" (1UL << (nr & 31)), "m" (*m));
}


/**
 * test_bit - Determine if a bit is set
 * @nr: the bit to test
 * @addr: the address of the memory location to check
 *
 * Test the value of the bit at position @nr in the memory pointed to by @addr.
 * This function uses bitwise operations to extract the value of the specified
 * bit and returns true if the bit is set (1), or false if the bit is not set (0).
 */
static inline bool test_bit(unsigned int nr, unsigned long *addr)
{
	return 1UL & (addr[BIT_WORD(nr)] >> (nr & (BITS_PER_LONG - 1)));
}


#endif /*_____BITOPS_H*/