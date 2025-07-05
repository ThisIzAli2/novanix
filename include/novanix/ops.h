/**
 * @author Ali Mirmohammad
 * @file ops.h
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
#ifndef __OPS_H
#define __OPS_H

#include <common/types.h>

Novanix::common::uint64_t  inline __udivdi3(Novanix::common::uint64_t  dividend, Novanix::common::uint64_t  divisor) {
    Novanix::common::uint64_t  quotient = 0;
    Novanix::common::uint64_t  remainder = 0;
    
    for (int i = 63; i >= 0; i--) {
        remainder <<= 1;
        remainder |= (dividend >> i) & 1;
        if (remainder >= divisor) {
            remainder -= divisor;
            quotient |= (1ULL << i);
        }
    }
    
    return quotient;
}


#endif