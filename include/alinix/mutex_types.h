/**
 * @author Ali Mirmohammad
 * @file mutex_types.h
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
 * 	- Kernel mutex types header files.
*/
#ifndef __ALINIX_KERNEL_MUTEX_TYPES_H
#define __ALINIX_KERNEL_MUTEX_TYPES_H


#include <alinix/spinlock_types.h>
#include <alinix/list.h>

/**
 * @brief Mutex data type.
*/
struct mutex {

#ifdef CONFIG_MUTEX_SPIN_ON_OWNER
	struct optimistic_spin_queue osq; /* Spinner MCS lock */
#endif /*CONFIG_MUTEX_SPIN_ON_OWNER*/
	struct list_head	wait_list;
#ifdef CONFIG_DEBUG_MUTEXES
	void			*magic;
#endif /*CONFIG_DEBUG_MUTEXES*/
#ifdef CONFIG_DEBUG_LOCK_ALLOC
	struct lockdep_map	dep_map;
#endif /*CONFIG_DEBUG_LOCK_ALLOC*/
};

#endif //__ALINIX_KERNEL_MUTEX_TYPES_H