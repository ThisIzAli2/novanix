/**
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


#ifndef MOUSE_H
#define MOUSE_H

#include <types.h>


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

typedef struct mouse_info{
    int x;
    int y;
    uint32_t buttons;  
}mouse_info_t;


#endif // MOUSE_H