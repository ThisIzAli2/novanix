/**
 * @author Ali Mirmohammad
 * @file memoryoperations.h
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
#ifndef __Novanix__COMMON__MEMORYOPERATIONS_H
#define __Novanix__COMMON__MEMORYOPERATIONS_H

#include <common/types.h>

namespace Novanix
{
    namespace common
    {
        #define phys2virt(x) ((x) + 3_GB)
        #define virt2phys(x) ((x) - 3_GB)

        class MemoryOperations
        {
        public:
            // Memory operations 
            static VOID* memmove(VOID* dstptr, const VOID* srcptr, uint32_t size);
            static int memcmp(const VOID* aptr, const VOID* bptr, uint32_t size);
            static VOID* memset(VOID* bufptr, char value, uint32_t size);
            static VOID* memcpy(VOID* dstptr, const VOID* srcptr, uint32_t size);
        };
    }
}

#endif