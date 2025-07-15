/**
 * @author Ali Mirmohammad
 * @file deviceheap.cpp
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
#include <system/memory/deviceheap.h>
#include <system/memory/heap.h>
#include <system/log.h>

using namespace Novanix;
using namespace Novanix::common;
using namespace Novanix::core;
using namespace Novanix::system;

uint32_t DeviceHeap::currentAddress = DEVICE_HEAP_START;

uint32_t DeviceHeap::AllocateChunk(uint32_t size)
{
    uint32_t ret = DeviceHeap::currentAddress;
    DeviceHeap::currentAddress += pageRoundUp(size);

    // Will propably never happen
    if(DeviceHeap::currentAddress >= DEVICE_HEAP_END)
        Log(Error, "Device heap is getting to big!");
    
    return ret;
}