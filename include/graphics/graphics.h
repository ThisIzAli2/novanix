/**
 * @author Ali Mirmohammad
 * @file graphics.h
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

#ifndef GRAPHICS_H
#define GRAPHICS_H

#define VGA_ADDRESS 0xA0000
#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 200

#ifdef __cplusplus
extern "C" {
#endif

// Set a pixel on screen at (x, y) to a color
void put_pixel(int x, int y, unsigned char color);

// Draw a filled rectangle
void draw_rect(int x, int y, int width, int height, unsigned char color);

// Clear the screen with a color

// Draw basic text at (x, y). You must implement a font or use BIOS font
void draw_text(int x, int y, const char* text, unsigned char color);

void gui();


#ifdef __cplusplus
}
#endif

#endif // GRAPHICS_H