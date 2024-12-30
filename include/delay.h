#ifndef __DELAY_H
#define __DELAY_H

#include <typing.hpp>

#define DELAY_CONSTANT 10

inline VOID delay(unsigned long long  time){
    while (time--);
}

#endif