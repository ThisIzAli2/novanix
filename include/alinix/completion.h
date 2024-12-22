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
 * @file completion.h
 * @abstract:
 * 	- Kernel completion header file implemented.
*/
#ifndef __ALINIX_KERNEL_COMPLETION_H
#define __ALINIX_KERNEL_COMPLETION_H

#include <alinix/kernel.h>
#include <alinix/swait.h>


struct completion {
	unsigned int done;
	struct swait_queue_head wait;
};



#endif // __ALINIX_KERNEL_COMPLETION_H