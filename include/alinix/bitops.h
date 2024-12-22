/**
 * @author Ali Mirmohammad
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
 * 	- Bitwise operations.
*/
#ifndef ___ALINIX_KERNEL_BIT_OPS_H
#define ___ALINIX_KERNEL_BIT_OPS_H

/**
 * @brief Useful bit operation as inline function. 
*/
static inline int test_and_set_bit(int nr, volatile unsigned long * addr)
{
	unsigned long mask = nr;
	unsigned long old;
	unsigned long flags;
	int set;

	set = (old & mask) ? 1 : 0;
	if (!set)
		*addr = old | mask;

	return set;
}




#endif // ___ALINIX_KERNEL_BIT_OPS_H