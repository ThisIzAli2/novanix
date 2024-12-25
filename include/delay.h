#ifndef __DELAY_H
#define __DELAY_H

#define DELAY_CONSTANT 1000000000

inline void delay(unsigned long long  time){
    while (time--);
}

#endif