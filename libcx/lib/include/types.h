/**
 * @author Ali Mirmohammad
 * @file types.h
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
#ifndef __NovanixLIB__TYPES_H
#define __NovanixLIB__TYPES_H

namespace Novanix
{
    #define STATIC_ASSERT(condition) typedef char p__LINE__[ (condition) ? 1 : -1];

    typedef char                        int8_t;
    typedef unsigned char               uint8_t;
    typedef short                       int16_t;
    typedef unsigned short              uint16_t;
    typedef int                         int32_t;
    typedef unsigned int                uint32_t;
    typedef long long int               int64_t;
    typedef unsigned long long int      uint64_t;
    typedef unsigned long long          uintptr_t;

    constexpr uint32_t operator"" _KB(unsigned long long no)
    {
        return no * 1024;
    }
    constexpr uint32_t operator"" _MB(unsigned long long no)
    {
        return no * (1024_KB);
    }
    constexpr uint32_t operator"" _GB(unsigned long long no)
    {
        return no * (1024_MB);
    }
}

#endif