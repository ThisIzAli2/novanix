/**
 * @author Ali Mirmohammad
 * @file fpu.h
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
#ifndef __Novanix__CORE__FPU_H
#define __Novanix__CORE__FPU_H

#include <common/types.h>

namespace Novanix
{
    namespace core
    {
        struct FPUControlWord
        {
            common::uint8_t InvalidOperand : 1;
            common::uint8_t DenormalOperand : 1;
            common::uint8_t ZeroDevide : 1;
            common::uint8_t Overflow : 1;
            common::uint8_t Underflow : 1;
            common::uint8_t Precision : 1;
            common::uint8_t reserved1 : 1;
            common::uint8_t reserved2 : 1;
            common::uint8_t PrecisionControl : 2;
            common::uint8_t RoundingControl : 2;
            common::uint8_t InfinityControl : 1;
            common::uint8_t reserved3 : 3;
        } __attribute__((packed));

        class FPU
        {
        public:
            static void Enable();
        };
    }
}

#endif