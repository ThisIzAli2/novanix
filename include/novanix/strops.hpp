#pragma once


#include <typing.hpp>

INTEGER __always_inline contains(const char *haystack, const char *needle) {
    int i, j;

    for (i = 0; haystack[i] != '\0'; i++) {
        // Check if the substring matches
        for (j = 0; needle[j] != '\0'; j++) {
            if (haystack[i + j] == '\0' || haystack[i + j] != needle[j]) {
                break;
            }
        }
        // If the entire substring matches
        if (needle[j] == '\0') {
            return 1; // Found
        }
    }

    return 0; // Not found
}