/**
 * @author Ali Mirmohammad
 * @file ops.cpp
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
#include <software/help/ops.h>

uint32_t strlen_kernel(const char* str) {
    uint32_t len = 0;
    while (str[len] != '\0') {
        len++;
    }
    return len;
}

// Converts a character to binary and stores it in a buffer (e.g., "01000001")
VOID char_to_binary(uint8_t c, char* buffer) {
    for (int i = 7; i >= 0; --i) {
        buffer[7 - i] = (c & (1 << i)) ? '1' : '0';
    }
    buffer[8] = '\0'; // Null terminator
}

// Example function to convert an entire string to binary
uint32_t string_to_binary(const char* str) {
    uint32_t result = 0;
    for (int i = 0; i < 4 && str[i] != '\0'; ++i) {
        result <<= 8;                  // Make room for next 8 bits
        result |= (uint8_t)str[i];     // Add the character
    }
    return result;
}

char  binary_to_char(const char* bin) {
    char result = 0;
    for (INTEGER i = 0; i < 8; ++i) {
        result <<= 1;
        if (bin[i] == '1') {
            result |= 1;
        }
    }
    return result;
}

// Converts a binary string like "01001000 01100101" to a normal string like "He"
// Assumes input is space-separated binary and output is pre-allocated
VOID binary_to_string(const char* binary_input, char* output) {
    uint32_t in_index = 0;
    uint32_t out_index = 0;
    char byte_str[9]; // 8 bits + null terminator
    int bit_count = 0;

    while (1) {
        char c = binary_input[in_index++];

        if (c == '\0') {
            if (bit_count == 8) {
                byte_str[8] = '\0';
                output[out_index++] = binary_to_char(byte_str);
            }
            break;
        }

        if (c == ' ') {
            if (bit_count == 8) {
                byte_str[8] = '\0';
                output[out_index++] = binary_to_char(byte_str);
                bit_count = 0;
            }
        } else {
            if (bit_count < 8) {
                byte_str[bit_count++] = c;
            }
        }
    }

    output[out_index] = '\0'; // Null-terminate the result
}