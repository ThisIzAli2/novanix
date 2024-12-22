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
 * @file heap.h
 * @abstract:
 *  - Kernel heap implementation for drivers memory.
*/
#ifndef _ALINIX_KERNEL_HEAP_H
#define _ALINIX_KERNEL_HEAP_H


#include <alinix/types.h>
#ifndef align_up
#define align_up(num, align) \
    (((num) + ((align) - 1)) & ~((align) - 1))
#endif

uint32_t pageRoundUp(uint32_t address);
uint32_t pageRoundDown(uint32_t address);
void* UserHeapMalloc(uint32_t size);
void* alignedMalloc(uint32_t size, uint32_t align);
void allignedFree(void* ptr);
void Free(void *ptr);

#define HEAP_INCREASE_SIZE 10_MB


/**
 * @brief Memory header data structure for kernel heap.
*/
struct MemoryHeader
{
    struct MemoryHeader* next;
    struct MemoryHeader* prev;
    bool allocated;
    uint32_t size;
} __attribute__((packed));
bool CheckForErrors();

#endif /*_ALINIX_KERNEL_HEAP_H*/