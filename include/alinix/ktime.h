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
 * @file ktime.h
 * @abstraction:
 * 	- Kernel time header file implemented.
*/
#ifndef __ALINIX_KERNEL_K_TIME_H
#define __ALINIX_KERNEL_K_TIME_H

#include <alinix/types.h>
#include <alinix/compiler.h>
#include <alinix/kernel.h>

#define PSEC_PER_NSEC			1000L


#define NSEC_PER_SEC	1000000000L
/* Located here for timespec[64]_valid_strict */
#define TIME64_MAX			((sint64_t)~((u64)1 << 63))
#define TIME64_MIN			(-TIME64_MAX - 1)

#define KTIME_MAX			((sint64_t)~((u64)1 << 63))
#define KTIME_MIN			(-KTIME_MAX - 1)
#define KTIME_SEC_MAX			(KTIME_MAX / NSEC_PER_SEC)
#define KTIME_SEC_MIN			(KTIME_MIN / NSEC_PER_SEC)

/**
 * @brief Kernel time settings function.
*/
static inline ktime_t ktime_set(const sint64_t secs, const unsigned long nsecs)
{
	if (unlikely(secs >= KTIME_SEC_MAX))
		return KTIME_MAX;

	return secs * NSEC_PER_SEC + (sint64_t)nsecs;
}


#endif // __ALINIX_KERNEL_K_TIME_H