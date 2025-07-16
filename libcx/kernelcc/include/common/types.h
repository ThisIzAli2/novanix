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
#ifndef Novanix__COMMON__TYPES_H
#define Novanix__COMMON__TYPES_H

#ifndef VOID
#define VOID void 
#endif

namespace Novanix
{
    namespace common
    {
        typedef char                        int8_t;
        typedef unsigned char               uint8_t;
        typedef short                       int16_t;
        typedef unsigned short              uint16_t;
        typedef int                         int32_t;
        typedef unsigned int                uint32_t;
        typedef long long int               int64_t;
        typedef unsigned long long int      uint64_t;
        typedef unsigned long long          uintptr_t;

        constexpr uint64_t divide64(uint64_t n, uint32_t base, uint32_t* r = 0)
        {
            uint64_t rem = n;
            uint64_t b = base;
            uint64_t res = 0, d = 1;
            uint32_t high = rem >> 32;

            /* Reduce the thing a bit first */
            if (high >= base) {
                    high /= base;
                    res = (uint64_t) high << 32;
                    rem -= (uint64_t) (high*base) << 32;
            }

            while ((int64_t)b > 0 && b < rem) {
                    b = b+b;
                    d = d+d;
            }

            do {
                    if (rem >= b) {
                            rem -= b;
                            res += d;
                    }
                    b >>= 1;
                    d >>= 1;
            } while (d);

            if(r)
                *r = rem;
            
            return res;
        }
    }
    constexpr common::uint32_t operator"" _KB(unsigned long long no)
    {
        return no * 1024;
    }
    constexpr common::uint32_t operator"" _MB(unsigned long long no)
    {
        return no * (1024_KB);
    }
    constexpr common::uint32_t operator"" _GB(unsigned long long no)
    {
        return no * (1024_MB);
    }
}

#endif