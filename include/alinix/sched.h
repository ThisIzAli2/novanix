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
 * @file sched.h
 * @abstract:
 * 	- Kernel sched.
*/
#ifndef __ALINIX_KERNEL_SCHED_H
#define __ALINIX_KERNEL_SCHED_H

#define TASK_UNINTERRUPTIBLE		0x00000002

enum {
	TASK_COMM_LEN = 16,
};

#endif // __ALINIX_KERNEL_SCHED_H