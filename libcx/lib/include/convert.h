/**
 * @author Ali Mirmohammad
 * @file convert.h
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
#ifndef __Novanix__CONVERT_H
#define __Novanix__CONVERT_H

#include <types.h>

namespace Novanix
{
    class Convert
    {
    public:
        static char* IntToString(int i);

        static char* IntToHexString(uint8_t w);
        static char* IntToHexString(uint16_t w);
        static char* IntToHexString(uint32_t w);

        static int StringToInt(char* string);
    };
}

#endif