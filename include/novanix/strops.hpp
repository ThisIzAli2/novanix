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