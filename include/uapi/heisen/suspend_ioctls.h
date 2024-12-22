/**
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

#ifndef __HEISEN_SUSPEND_IOCTLS_H
#define __HEISEN_SUSPEND_IOCTLS_H


#include <heisen/typing.h>

struct resume_swap_area {
	__kernel_loff_t offset;
	uint32_t dev;
} __attribute__((packed));



#endif // __HEISEN_SUSPEND_IOCTLS_H