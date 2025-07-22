#ifndef __NOVANIX_KERNEL_GAMING_GENERIC_HPP
#define __NOVANIX_KERNEL_GAMING_GENERIC_HPP

#include <common/init.hpp>

#define DELAY_CONSTANT_GAME 1000000000000

class Snake{
    public:
        Snake();
        ~Snake();

    private:
        volatile INTEGER countdown;
        VOID delay_time(){
            for (countdown = 0; countdown < DELAY_CONSTANT_GAME;countdown++){}
        }
        VOID print_stuff(){
            delay_time();
            printk(VGA_WHITE,"-",0);
        }
    public:
        VOID print_s(){
            print_stuff();
        }
        
};


#endif /*__NOVANIX_KERNEL_GAMING_GENERIC_HPP*/