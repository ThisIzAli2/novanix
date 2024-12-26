#ifndef __DELAY_H
#define __DELAY_H

#define DELAY_CONSTANT 10

inline void delay(unsigned long long  time){
    while (time--);
}

#endif