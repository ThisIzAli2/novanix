/**
 * @file circle.h
 * @author Ali Mirmohammad
 * 
 ** This file is part of Novanix.

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
#ifndef __NOVANIX_KERNEL_CIRCLE_H
#define __NOVANIX_KERNEL_CIRCLE_H

#include <common/init.hpp>

#ifndef VGA_WIDTH
#define VGA_WIDTH 320
#endif // VGA_WIDTH

#ifndef VGA_HEIGHT
#define VGA_HEIGHT 200
#endif // VGA_HEIGHT

#ifndef VGA_ADDRESS
#define VGA_ADDRESS 0xA0000
#endif // VGA_ADDRESS

void put_pixel(int x, int y, uint8_t color);



#endif /*__NOVANIX_KERNEL_CIRCLE_H*/