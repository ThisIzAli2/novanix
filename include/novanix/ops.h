#ifndef __OPS_H
#define __OPS_H

#include <common/types.h>

Novanix::common::uint64_t  inline __udivdi3(Novanix::common::uint64_t  dividend, Novanix::common::uint64_t  divisor) {
    Novanix::common::uint64_t  quotient = 0;
    Novanix::common::uint64_t  remainder = 0;
    
    for (int i = 63; i >= 0; i--) {
        remainder <<= 1;
        remainder |= (dividend >> i) & 1;
        if (remainder >= divisor) {
            remainder -= divisor;
            quotient |= (1ULL << i);
        }
    }
    
    return quotient;
}


#endif