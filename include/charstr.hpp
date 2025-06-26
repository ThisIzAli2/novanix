#pragma once

#include <common/init.hpp>

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