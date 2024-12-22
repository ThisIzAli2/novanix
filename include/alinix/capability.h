/**
 * @author Ali Mirmohammad
 * @file capability.h
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
 * @file capability.h
 * @abstract:
 * 	- Kernel capability header file implemented.
*/
#ifndef __ALINIX_KERNEL_CAPABILITY_H
#define __ALINIX_KERNEL_CAPABILITY_H

#include <alinix/types.h>

#define CAP_SYS_TIME 25
#define	EPERM		 1	/* Operation not permitted */

/**
 * @brief Check if the current process has the specified capability.
 *
 * The `capable` function checks whether the current process has the specified
 * capability. In this simplified version, the function always returns `true`,
 * indicating that the capability check is always successful.
 *
 * @param cap The capability to check for. This is an integer value representing
 *            a specific capability (e.g., `CAP_SYS_ADMIN`, `CAP_NET_ADMIN`).
 *
 * @return `true` always. This indicates that the process is always considered
 *         capable of performing the action associated with the specified capability.
 *
 * @note This function is implemented as a static inline function to avoid
 *       function call overhead and to allow the compiler to optimize its
 *       usage more effectively.
 */
static inline bool capable(int cap)
{
	return true;
}

#endif // __ALINIX_KERNEL_CAPABILITY_H