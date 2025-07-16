/**
 * @file circle.cpp
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

#include <math/circle.h>


void put_pixel(int x, int y, uint8_t color) {
    uint8_t* vga = (uint8_t*) VGA_ADDRESS;
    if (x >= 0 && x < VGA_WIDTH && y >= 0 && y < VGA_HEIGHT)
        vga[y * VGA_WIDTH + x] = color;
}

void draw_circle(int xc, int yc, int radius, uint8_t color) {
    int x = 0, y = radius;
    int d = 3 - 2 * radius;

    while (x <= y) {
        // 8 symmetrical points
        put_pixel(xc + x, yc + y, color);
        put_pixel(xc - x, yc + y, color);
        put_pixel(xc + x, yc - y, color);
        put_pixel(xc - x, yc - y, color);
        put_pixel(xc + y, yc + x, color);
        put_pixel(xc - y, yc + x, color);
        put_pixel(xc + y, yc - x, color);
        put_pixel(xc - y, yc - x, color);

        if (d < 0)
            d += 4 * x + 6;
        else {
            d += 4 * (x - y) + 10;
            y--;
        }
        x++;
    }
}