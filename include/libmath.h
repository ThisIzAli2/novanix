/**
 * @author Ali Mirmohammad
 * @file libmath.h
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

#ifndef __LIB_MATH_H
#define __LIB_MATH_H

#include <typing.hpp>

INTEGER inline power(INTEGER base, INTEGER exponent) {
    INTEGER result = 1;

    // If exponent is negative, handle it (for simplicity, we'll just return 0 here)
    if (exponent < 0) {
        return 0; // You can handle this case as needed (e.g., return a floating-point result)
    }

    // Multiply base by itself exponent times
    for (INTEGER i = 0; i < exponent; i++) {
        result *= base;
    }

    return result;
}

#endif