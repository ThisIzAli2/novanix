/**
 * @author Ali Mirmohammad
 * @file heap.h
 * @Credits remco123
 ** This file is part of Novanix.

**Novanix is free software: you can redistribute it and/or modify
**it under the terms of the GNU Affero General Public License as published by
**the Free Software Foundation, either version 3 of the License, or
**(at your option) any later version.

**Novanix is distributed in the hope that it will be useful,
**but WITHOUT ANY WARRANTY; without even the implied warranty of
**MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
**GNU Affero General Public License for more details.

**You should have received a copy of the GNU Affero General Public License
**along with Novanix. If not, see <https://www.gnu.org/licenses/>.
*/
#ifndef __NovanixLIB__HEAP_H
#define __NovanixLIB__HEAP_H

#include <types.h>

namespace Novanix
{
    #ifndef align_up
    #define align_up(num, align) \
        (((num) + ((align) - 1)) & ~((align) - 1))
    #endif

    uint32_t pageRoundUp(uint32_t address);
    uint32_t pageRoundDown(uint32_t address);

    #define HEAP_INCREASE_SIZE 10_MB

    struct MemoryHeader
    {
        MemoryHeader* next;
        MemoryHeader* prev;
        bool allocated;
        uint32_t size;
    } __attribute__((packed));

    class UserHeap
    {
    private:
        static uint32_t startAddress;
        static uint32_t endAddress;
        static uint32_t maxAddress;

        static MemoryHeader* firstHeader;

    public:
        static void Initialize();
        static void PrintMemoryLayout();

        static void* Malloc(uint32_t size);
        static void Free(void* ptr);

        static void* alignedMalloc(uint32_t size, uint32_t align);
        static void allignedFree(void* ptr);
    };
}

#endif