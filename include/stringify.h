#ifndef __STRINGIFY_H
#define __STRINGIFY_H

#include <typing.hpp>


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