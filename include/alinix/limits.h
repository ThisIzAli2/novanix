/**
 * @author Ali Mirmohammad
 * @file limits.h
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
 *  - Kernel limits implemented.
*/
#ifndef __ALINIX_KERNEL_LIMITS_H
#define __ALINIX_KERNEL_LIMITS_H


/**
 * @brief :
 *  - Useful macros for limit.h
*/
#define USHRT_MAX	((unsigned short)~0U)
#define SHRT_MAX	((short)(USHRT_MAX >> 1))
#define SHRT_MIN	((short)(-SHRT_MAX - 1))
#define INT_MAX		((int)(~0U >> 1))
#define INT_MIN		(-INT_MAX - 1)
#define UINT_MAX	(~0U)
#define LONG_MAX	((long)(~0UL >> 1))
#define LONG_MIN	(-LONG_MAX - 1)
#define ULONG_MAX	(~0UL)
#define LLONG_MAX	((long long)(~0ULL >> 1))
#define LLONG_MIN	(-LLONG_MAX - 1)
#define ULLONG_MAX	(~0ULL)
#define UINTPTR_MAX	ULONG_MAX
#define	MAX_SCHEDULE_TIMEOUT		LONG_MAX

#endif // __ALINIX_KERNEL_LIMITS_H