/**
 * @author Ali Mirmohammad
 * @file graphics.cpp
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
#include <graphics/graphics.h>


void put_pixel(int x, int y, unsigned char color) {
    if (x < 0 || x >= SCREEN_WIDTH || y < 0 || y >= SCREEN_HEIGHT) return;
    unsigned char* video = (unsigned char*)VGA_ADDRESS;
    video[y * SCREEN_WIDTH + x] = color;
}

void draw_rect(int x, int y, int width, int height, unsigned char color) {
    for (int dy = 0; dy < height; dy++) {
        for (int dx = 0; dx < width; dx++) {
            put_pixel(x + dx, y + dy, color);
        }
    }
}



// Stub for draw_text (replace with actual bitmap/font handling)
void draw_text(int x, int y, const char* text, unsigned char color) {
    // You’ll need a font array like 8x8 font bitmaps to implement this.
    // For now, this can be left as a no-op or used with BIOS interrupt if using real mode.
}
