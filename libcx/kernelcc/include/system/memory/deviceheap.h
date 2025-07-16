/**
 * @author Ali Mirmohammad
 * @file deviceheap.h
 * @credits Remco123
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
#ifndef __Novanix__SYSTEM__DEVICEHEAP_H
#define __Novanix__SYSTEM__DEVICEHEAP_H

#include <core/virtualmemory.h>
#include <common/types.h>

namespace Novanix
{
    namespace system
    {
        // Memory reserved for devices, 100MB Should be more than enough
        #define DEVICE_HEAP_SIZE 100_MB

        #define DEVICE_HEAP_START (KERNEL_HEAP_START + KERNEL_HEAP_SIZE + 4_MB)
        #define DEVICE_HEAP_END (DEVICE_HEAP_START + DEVICE_HEAP_SIZE)

        // Class that can allocate memory for memory mapped devices
        class DeviceHeap
        {
        private:
            // Current address of last memory allocation
            // Will increase on every allocation
            static common::uint32_t currentAddress;
        public:
            // Allocate a chunck of memory in the virtual address space
            // Must be a page aligned size
            // Note: Memory needs to be mapped to right address afterwards, function does not include this
            static common::uint32_t AllocateChunk(common::uint32_t size);
        };
    }
}


#endif