/**
 * @author Ali Mirmohammad
 * @file iommufd_utils.h
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
 * 	- Kernel I/O utils.
*/
#ifndef __IOMMUFD_UTILS_H
#define __IOMMUFD_UTILS_H

# define __BITS_PER_LONG 32
#define BITS_PER_BYTE 8
#define BITS_PER_LONG __BITS_PER_LONG
#define BIT_MASK(nr) (1UL << ((nr) % __BITS_PER_LONG))
#define BIT_WORD(nr) ((nr) / __BITS_PER_LONG)


/**
 * set_bit - Set a bit in a memory address
 * @nr: bit number to set
 * @addr: address of the memory location
 *
 * This function sets the specified bit in the memory location pointed to
 * by @addr. It calculates the appropriate mask and word within the memory
 * location to modify and then sets the bit using a bitwise OR operation.
 *
 * The function uses `BIT_MASK` to create a mask for the specified bit
 * and `BIT_WORD` to determine the word within the memory location.
 *
 * Example usage:
 *     unsigned long flags = 0;
 *     set_bit(3, &flags); // Sets the 3rd bit in the flags variable
 */
static inline void set_bit(unsigned int nr, unsigned long *addr)
{
	unsigned long mask = BIT_MASK(nr);
	unsigned long *p = ((unsigned long *)addr) + BIT_WORD(nr);

	*p |= mask;
}

/**
 * test_bit - Test if a bit is set in a memory address
 * @nr: bit number to test
 * @addr: address of the memory location
 *
 * This function checks if the specified bit is set in the memory location pointed to
 * by @addr. It calculates the appropriate word within the memory location and then
 * checks the bit using a bitwise AND and shift operation.
 *
 * The function uses `BIT_WORD` to determine the word within the memory location
 * and then shifts the word to the right to isolate the desired bit.
 *
 * Returns: true if the bit is set, false otherwise.
 *
 * Example usage:
 *     unsigned long flags = 0x8; // binary: 0000 1000
 *     bool is_set = test_bit(3, &flags); // Tests if the 3rd bit is set
 *     // is_set will be true
 */
static inline bool test_bit(unsigned int nr, unsigned long *addr)
{
	return 1UL & (addr[BIT_WORD(nr)] >> (nr & (BITS_PER_LONG - 1)));
}


#endif /*__IOMMUFD_UTILS_H*/

