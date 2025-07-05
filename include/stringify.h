/**
 * @author Ali Mirmohammad
 * @file stringify.h
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
#ifndef __STRINGIFY_H
#define __STRINGIFY_H

#include <typing.hpp>


/**
 * @brief Stringify the integer 
 */
char* stringify(INTEGER num){
    static char str[20];  // Make sure this is large enough to hold the result (including negative sign)
    INTEGER i = 0;
    BOOL isNegative = false;

    // Handle 0 explicitly
    if (num == 0) {
        str[i++] = '0';
        str[i] = '\0';
        return str;
    }

    // Handle negative numbers
    if (num < 0) {
        isNegative = true;
        num = -num;  // Make the number positive for now
    }

    // Process each digit and store in str[]
    while (num > 0) {
        str[i++] = (num % 10) + '0';  // Convert digit to character
        num = num / 10;  // Remove the last digit
    }

    // Add negative sign if needed
    if (isNegative) {
        str[i++] = '-';
    }

    // Null-terminate the string
    str[i] = '\0';

    // Reverse the string to get the correct order
    INTEGER start = 0;
    INTEGER end = i - 1;
    while (start < end) {
        char temp = str[start];
        str[start] = str[end];
        str[end] = temp;
        start++;
        end--;
    }

    return str;
}
#endif