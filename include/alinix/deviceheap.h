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
 * @file deviceheap.h
 * Abstraction :
 *      - Provide some utility for the device heap management.
*/

#ifndef __ALINIX_KERNEL_DEVICE_HEAP_H   
#define __ALINIX_KERNEL_DEVICE_HEAP_H

#include <alinix/types.h>

#define DEVICE_HEAP_SIZE 100_MB

#define DEVICE_HEAP_START (KERNEL_HEAP_START + KERNEL_HEAP_SIZE + 4_MB)
#define DEVICE_HEAP_END (DEVICE_HEAP_START + DEVICE_HEAP_SIZE)


// Current address of last memory allocation
// Will increase on every allocation
static uint32_t currentAddress;

// Allocate a chunck of memory in the virtual address space
// Must be a page aligned size
// Note: Memory needs to be mapped to right address afterwards, function does not include this
uint32_t AllocateChunk(uint32_t size);


#endif /*__ALINIX_KERNEL_DEVICE_HEAP_H*/