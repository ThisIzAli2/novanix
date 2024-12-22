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
 * @file err.h
 * @abstraction:
 * 	- Kernel error header file.
*/
#ifndef _ALINIX_KERNEL_ERR_H
#define _ALINIX_KERNEL_ERR_H

#include <alinix/compiler_types.h>

/**
 * @brief Convert a pointer to a long error code.
 *
 * The `PTR_ERR` function takes a pointer and converts it to a long integer 
 * representing an error code. This is often used in Linux kernel code to 
 * return error codes through pointers.
 *
 * @param ptr The pointer to be converted to an error code.
 *
 * @return The error code as a long integer.
 *
 * @note This function is implemented as a static inline function to avoid 
 *       function call overhead and to allow the compiler to optimize its 
 *       usage more effectively.
 */
static inline long  PTR_ERR(const void *ptr)
{
	return (long) ptr;
}

#endif /*_ALINIX_KERNEL_ERR_H*/