/**
 * @author Ali Mirmohammad
 * @file charstr.hpp
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

#ifndef __NOVANIX_KERNEL_CHARSTR_HPP
#define __NOVANIX_KERNEL_CHARSTR_HPP

#include <common/init.hpp>


/**
 * @brief A function used to compare the two strings, mainly designed for the commands
 */
INTEGER __always_inline cmd_cmp(const char* str1, const char* str2) {
    // Compare each character of both strings
    while (*str1 != '\0' && *str2 != '\0') {
        if (*str1 != *str2) {
            return *str1 - *str2;  // Return the difference if characters are different
        }
        str1++;
        str2++;
    }

    // If both strings are the same length, return 0 (strings are equal)
    // Otherwise, return the difference between the null terminator of one string and the other string's character
    return *str1 - *str2;
}

#endif /*__NOVANIX_KERNEL_CHARSTR_HPP*/