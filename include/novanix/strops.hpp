/**
 * @author Ali Mirmohammad
 * @file strops.hpp
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
#pragma once


#include <typing.hpp>

INTEGER __always_inline contains(const char *array, INTEGER array_size, const char *substring) {
    INTEGER i, j;

    // Iterate through the array
    for (i = 0; i <= array_size - 1; i++) {
        // Check if the substring matches starting at index i
        for (j = 0; substring[j] != '\0'; j++) {
            if (i + j >= array_size || array[i + j] != substring[j]) {
                break; // Mismatch found
            }
        }

        // If we completed the substring comparison, it's a match
        if (substring[j] == '\0') {
            return 1; // Substring exists
        }
    }

    return 0; // Substring does not exist
}