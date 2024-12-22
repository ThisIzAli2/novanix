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
 * @file lockref.h
 * @abstract:
 * 	- Kernel locking thread.
*/
#ifndef __ALINIX_KERNEL_LOCK_REF_H
#define __ALINIX_KERNEL_LOCK_REF_H

#include <alinix/kernel.h>

struct lockref {
	union {
#if USE_CMPXCHG_LOCKREF
		aligned_u64 lock_count;
#endif /*USE_CMPXCHG_LOCKREF*/
		struct {
			spinlock_t lock;
			int count;
		};
	};
};
#endif // __ALINIX_KERNEL_LOCK_REF_H