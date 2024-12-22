/**
 * @author Ali Mirmohammad
 * @file pixel.h
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

#ifndef __ALINIX_PIXEL_H
#define __ALINIX_PIXEL_H

#include <alinix/types.h>

/**
 * @brief Draws a pixel at the specified coordinates with the given color.
 *
 * This function sets a pixel on the screen at the specified (x, y) position 
 * to the given VGA color. The function directly manipulates the VGA memory, 
 * which is mapped starting at address 0xA0000.
 *
 * @param pos_x The x-coordinate of the pixel (horizontal position).
 * @param pos_y The y-coordinate of the pixel (vertical position).
 * @param VGA_COLOR The color to set the pixel to, represented as an unsigned char.
 *
 * This function uses the standard 320x200 256-color VGA mode, where each 
 * pixel is represented by a single byte in the VGA memory. The memory is 
 * accessed directly by calculating the appropriate offset for the given 
 * coordinates.
 *
 * Example usage:
 * @code
 * inline void putpixel(int pos_x, int pos_y, unsigned char VGA_COLOR) {
 *     unsigned char* location = (unsigned char*)0xA0000 + 320 * pos_y + pos_x;
 *     *location = VGA_COLOR;
 * }
 * 
 * int main() {
 *     putpixel(100, 50, 15); // Set pixel at (100, 50) to color 15
 *     return 0;
 * }
 * @endcode
 *
 * @note This function is intended for use in environments where direct 
 * access to VGA memory is allowed, such as certain embedded systems or 
 * custom operating systems. It may not work in protected or modern 
 * operating systems without appropriate privileges.
 */
inline void putpixel(int pos_x,int pos_y,unsigned char VGA_COLOR){
    unsigned char* location = (unsigned char*)0xA0000 + 320 * pos_y + pos_x;
    *location = VGA_COLOR;
}


#endif /*__ALINIX_PIXEL_H*/