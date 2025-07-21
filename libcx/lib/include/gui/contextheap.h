/**
 * @author Ali Mirmohammad
 * @file contextheap.h
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
#ifndef __Novanix__GUI__CONTEXTHEAP_H
#define __Novanix__GUI__CONTEXTHEAP_H

#include <types.h>

namespace Novanix
{
    //Class that provides functions for allocating memory space for contexts.
    //Note: Memory region is not allocated, just a block that is reserved after allocating.
    class ContextHeap
    {
    public:
        static void Init();
        //Allocate a area of memory, blocks is in units per 4096 bytes
        static uint32_t AllocateArea(uint32_t blocks);
        //Free area of memory
        static void FreeArea(uint32_t address, uint32_t blocks);
        //Get amount of memory used as factor [0-1]
        static double MemoryUsage();
    };
}

#endif