/**
 * @author Ali Mirmohammad
 * @file convert.h
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
#ifndef Novanix__COMMON__CONVERT_H
#define Novanix__COMMON__CONVERT_H

#include <common/types.h>
#include <common/memoryoperations.h>

namespace Novanix
{
    namespace common
    {
        class Convert
        {
        public:
            static char* IntToString(int i);
            static char* IntToString32(uint32_t i);

            static char* IntToHexString(common::uint8_t w);
            static char* IntToHexString(common::uint16_t w);
            static char* IntToHexString(common::uint32_t w);

            static int StringToInt(char* string);
            static uint32_t HexToInt(char* string);
        };
    }
}

#endif