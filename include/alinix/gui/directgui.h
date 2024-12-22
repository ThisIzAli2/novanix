/**
 * @file directgui.h
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
 * @abstract:
 *  - Direct GUI implemented.
*/
#ifndef __ALINIX_KERNEL_DIRECT_GUI_H
#define __ALINIX_KERNEL_DIRECT_GUI_H

#include <alinix/types.h>
#include <alinix/gui/canvas.h>

bool RequestFramebuffer();
Canvas* GetCanvas();

void SetPixel(int x, int y, uint32_t color);
uint32_t GetPixel(int x, int y);

void Clear();
void Clear(uint32_t color);
void DrawHorizontalLine(uint32_t color, int dx, int x1, int y1);
void DrawVerticalLine(uint32_t color, int dx, int x1, int y1);
void DrawLine(uint32_t color, int x1, int y1, int x2, int y2);
void DrawDiagonalLine(uint32_t color, int dx, int dy, int x1, int y1);
void DrawRect(uint32_t color, int x, int y, int width, int height);
void DrawFillRect(uint32_t color, int x_start, int y_start, int width, int height);
void DrawCircle(uint32_t color, int x_center, int y_center, int radius);
void DrawFillCircle(uint32_t color, int x_center, int y_center, int radius);
void DrawEllipse(uint32_t color, int x_center, int y_center, int x_radius, int y_radius);

void DrawChar(char character, int x, int y, uint32_t color);
// void DrawString(char* string, int x, int y, uint32_t color);
//? Change above?


#endif  /*__ALINIX_KERNEL_DIRECT_GUI_H*/