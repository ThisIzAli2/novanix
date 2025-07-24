/**
 * @author Ali Mirmohammad
 * @file gaming_generic.hpp
 ** This file is part of Novanix.

**Novanix is free software: you can redistribute it and/or modify
**it under the terms of the GNU Affero General Public License as published by
**the Free Software Foundation, either version 3 of the License, or
**(at your option) any later version.

**Novanix is distributed in the hope that it will be useful,
**but WITHOUT ANY WARRANTY; without even the implied warranty of
**MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
**GNU Affero General Public License for more details.

**You should have received a copy of the GNU Affero General Public License
**along with Novanix. If not, see <https://www.gnu.org/licenses/>.
*/
#ifndef __NOVANIX_KERNEL_GAMING_GENERIC_HPP
#define __NOVANIX_KERNEL_GAMING_GENERIC_HPP

#include <common/init.hpp>

#define DELAY_CONSTANT_GAME 100000000

#define CLEAN printk(VGA_WHITE,"",1);

#define AWAIT_CONSTANT 30

#define PRINT_PIPE printk(VGA_WHITE,"|",1);
#define DASH_SIGN "-"

#define DASH 

#define PRINT_SLASH printk(VGA_WHITE,"/",0);

#define PRINT_BACK_SLASH printk(VGA_WHITE,"\\",0);

#define NEXT_LINE printk(VGA_WHITE,"",1);


class Snake{
    private:
    volatile INTEGER k;
        volatile INTEGER countdown;
        VOID delay_time(){
            for (countdown = 0; countdown < DELAY_CONSTANT_GAME;countdown++){}
        }
        VOID print_stuff(){
            delay_time();
            DASH
            // printk(VGA_WHITE,"",1);
        }
        VOID print_p(){
            PRINT_PIPE
        }
        VOID extend(){
            String::strcat(DASH_SIGN,DASH_SIGN);
        }
    public:
        VOID print_s(){
            for (INTEGER i = 0;i < AWAIT_CONSTANT;i++){
                if (k % 2 == 0){
                    print_p(); 
                    // extend();
                } else{
                    DASH
                }
                print_stuff();
                k++;
            }
            CLEAN
        }
        
};


#endif /*__NOVANIX_KERNEL_GAMING_GENERIC_HPP*/