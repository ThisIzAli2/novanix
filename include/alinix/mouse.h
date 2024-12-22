/**
 * @author Ali Mirmohammad
 ** This file is part of AliNix.

**AliNix is free software: you can redistribute it and/or modify
**it under the terms of the GNU Affero General Public License as published by
**the Free Software Foundation, either version 3 of the License, or
**(at your option) any later version.

**AliNix is distributed in the hope that it will be useful,
**but WITHOUT ANY WARRANTY; without even the implied warranty of
**MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
**GNU Affero General Public License for more details.

**You should have received a copy of the GNU Affero General Public License
**along with AliNix. If not, see <https://www.gnu.org/licenses/>.
*/

/**
 * @file mouse.h
 * @abstraction:
 *  - Implementation of the kernel mouse driver.
*/
#ifndef __ALINIX_KERNEL_MOUSE_H
#define __ALINIX_KERNEL_MOUSE_H

#include <alinix/types.h>


#define MOUSE_PORT 0x60
#define MOUSE_STATUS  0x80
#define MOUSE_ABIT 0x02
#define MOUSE_BBIT 0x01
#define MOUSE_WRITE  0xD4
#define MOUSE_F_BIT  0x20
#define MOUSE_V_BIT  0x08


/*Mouse clocks defined here*/


#define LEFT_CLICK      0x1
#define RIGHT_CLICK     0x2
#define MIDDLE_CLICK    0x4


/**
 * @brief Mouse info for the kernel.
*/
typedef struct mouse_info{
    int x;
    int y;
    uint32_t buttons;  
}mouse_info_t;

// void mouse_handler();
// void mouse_init();
// void mouse_check_bounds() ;
// uint8_t mouse_read() ;
// void mouse_write(uint8_t write) ;
// void mouse_wait(uint8_t type) ;
// mouse_info_t *get_mouse_info();
#endif // __ALINIX_KERNEL_MOUSE_H