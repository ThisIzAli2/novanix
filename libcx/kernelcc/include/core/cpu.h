/**
 * @author Ali Mirmohammad
 * @file cpu.h
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
#ifndef __Novanix__CORE__CPU_H
#define __Novanix__CORE__CPU_H

#include <common/types.h>

namespace Novanix
{
    namespace core
    {
        #define EDX_SSE2 (1 << 26) // Streaming SIMD Extensions 2
        #define EDX_FXSR (1 << 24) // Can we use the fxsave/fxrstor instructions?

        class CPU
        {
        public:
            static void PrintVendor();
            static void EnableFeatures();
        };        
    }
}

#endif