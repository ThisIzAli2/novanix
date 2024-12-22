/**
 * @author Ali Mirmohammad
 * @file swait.h
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
 * 	- Kernel swait header file.
*/
#ifndef __ALINIX_KERNEL_SWAIT_H
#define __ALINIX_KERNEL_SWAIT_H

#include <alinix/kernel.h>
#include <alinix/spinlock_types.h>
#include <alinix/types.h>


struct swait_queue_head {
	raw_spinlock_t		lock;
	struct list_head	task_list;
};

#endif /*__ALINIX_KERNEL_SWAIT_H*/