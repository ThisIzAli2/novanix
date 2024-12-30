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