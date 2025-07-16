/**
 * @author Ali Mirmohammad
 * @file sharedmem.h
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
#ifndef __Novanix__SYSTEM__MEMORY__SHAREDMEM_H
#define __Novanix__SYSTEM__MEMORY__SHAREDMEM_H

#include <system/tasking/process.h>

namespace Novanix
{
    namespace system
    {
        class SharedMemory
        {
        public:
            /**
             * Create a shared area of memory between processes
             * Proc1: Procces 1 where the memory needs to be present
             * Proc2: Process 2 where the memory needs to be present
             * virtStart: The virtual start of the memory region
             * len: The length of the memory region
            */
            static bool CreateSharedRegion(Process* proc1, Process* proc2, common::uint32_t virtStart, common::uint32_t len);
            /**
             * Create a shared area of memory between processes
             * Proc1: Procces 1 where the memory needs to be present
             * Proc2: Process 2 where the memory needs to be present
             * virtStart1: The virtual start of the memory region for process 1
             * virtStart2: The virtual start of the memory region for process 2
             * len: The length of the memory region
            */
            static bool CreateSharedRegion(Process* proc1, Process* proc2, common::uint32_t virtStart1, common::uint32_t virtStart2, common::uint32_t len);
            /**
             * Remove shared memory between 2 processes 
            */
            static bool RemoveSharedRegion(Process* proc1, Process* proc2, common::uint32_t virtStart, common::uint32_t len);
            /**
             * Remove shared memory between 2 processes 
            */
            static bool RemoveSharedRegion(Process* proc1, Process* proc2, common::uint32_t virtStart1, common::uint32_t virtStart2, common::uint32_t len);
        };
    }
}

#endif