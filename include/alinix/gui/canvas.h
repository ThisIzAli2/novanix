/**
 * @author Ali Mirmohammad
 * @file virtualfilesystem.h
 * *************************************IMPORTANT ALINIX LICENSE TERM********************************************
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
 *  - GUI and canvas header file.
*/
#ifndef __ALINIX_KERNEL_GUI_CANVAS_H
#define __ALINIX_KERNEL_GUI_CANVAS_H

#include <alinix/types.h>
#include <alinix/gui/fonts/font.h>



#if defined(__cplusplus)

class Canvas
{
private:
    void DrawCircleHelper(int x, int y, int radius, uint32_t corner, uint32_t color);
    void FillCircleHelper(int x, int y, int radius, uint32_t corner, int delta, uint32_t color);
public:
    ////////////////////////////
    //!NOTE: These properties should be only added if it is a c++ class, otherwise, has to be declared as local variable.
    void* bufferPointer;
    int Width;
    int Height;
    ////////////////////////////

    Canvas(void* buffer, int w, int h);

    void SetPixel(int x, int y, uint32_t color);
    uint32_t GetPixel(int x, int y);

    void Clear();
    void Clear(uint32_t color);
    void DrawHorizontalLine(uint32_t color, int dx, int x1, int y1);
    void DrawVerticalLine(uint32_t color, int dx, int x1, int y1);
    void DrawLine(uint32_t color, int x1, int y1, int x2, int y2);
    void DrawDiagonalLine(uint32_t color, int dx, int dy, int x1, int y1);
    void DrawRect(uint32_t color, int x, int y, int width, int height);
    void DrawRoundedRect(uint32_t color, int x, int y, int width, int height, int radius);
    void DrawFillRoundedRect(uint32_t color, int x, int y, int width, int height, int radius);
    void DrawFillRect(uint32_t color, int x_start, int y_start, int width, int height);
    void DrawCircle(uint32_t color, int x_center, int y_center, int radius);
    void DrawFillCircle(uint32_t color, int x_center, int y_center, int radius);
    void DrawEllipse(uint32_t color, int x_center, int y_center, int x_radius, int y_radius);

    // void DrawString(Font* font, char* string, int x, int y, uint32_t color);
};

#else 
typedef struct {
    void* bufferPointer;
    int Width;
    int Height;
} Canvas;

static void* bufferPointer;
static int Width;
static int Height;
Canvas* Canvas_Create(void* buffer, int w, int h);

// void Canvas_SetPixel(Canvas* canvas, int x, int y, uint32_t color);
void Canvas_SetPixel(int x, int y, uint32_t color);
// uint32_t Canvas_GetPixel(Canvas* canvas, int x, int y);
uint32_t Canvas_GetPixel(int x, int y);

void Canvas_Clear(Canvas* canvas);
void Canvas_ClearColor(Canvas* canvas, uint32_t color);
void Canvas_DrawHorizontalLine(Canvas* canvas, uint32_t color, int dx, int x1, int y1);
void Canvas_DrawVerticalLine(Canvas* canvas, uint32_t color, int dx, int x1, int y1);
void Canvas_DrawLine(Canvas* canvas, uint32_t color, int x1, int y1, int x2, int y2);
void Canvas_DrawDiagonalLine(Canvas* canvas, uint32_t color, int dx, int dy, int x1, int y1);
void Canvas_DrawRect(Canvas* canvas, uint32_t color, int x, int y, int width, int height);
void Canvas_DrawRoundedRect(Canvas* canvas, uint32_t color, int x, int y, int width, int height, int radius);
void Canvas_DrawFillRoundedRect(Canvas* canvas, uint32_t color, int x, int y, int width, int height, int radius);
void Canvas_DrawFillRect(Canvas* canvas, uint32_t color, int x_start, int y_start, int width, int height);
void Canvas_DrawCircle(Canvas* canvas, uint32_t color, int x_center, int y_center, int radius);
void Canvas_DrawFillCircle(Canvas* canvas, uint32_t color, int x_center, int y_center, int radius);
void Canvas_DrawEllipse(Canvas* canvas, uint32_t color, int x_center, int y_center, int x_radius, int y_radius);

void Canvas_DrawString(Canvas* canvas, struct Font* font, char* string, int x, int y, uint32_t color);

void Canvas_Destroy(Canvas* canvas);

void DrawLine(uint32_t color, int x1, int y1, int x2, int y2);

void DrawDiagonalLine(uint32_t color, int dx, int dy, int x1, int y1);
void DrawVerticalLine(uint32_t color, int dy, int x1, int y1);
void DrawHorizontalLine(uint32_t color, int dx, int x1, int y1);


void FillCircleHelper(int x, int y, int radius, uint32_t corner, int delta, uint32_t color);
void DrawCircleHelper(int x, int y, int radius, uint32_t corner, uint32_t color);
// void Clear();

void DrawFillRoundedRect(uint32_t color, int x, int y, int width, int height, int radius);

void DrawFillRect(uint32_t color, int x_start, int y_start, int width, int height);

void DrawRoundedRect(uint32_t color, int x, int y, int width, int height, int radius);
void DrawRect(uint32_t color, int x, int y, int width, int height);

void DrawString(struct Font* font, char* string, int x, int y, uint32_t color);

void Clear(uint32_t color);
#endif /*__cplusplus*/

#endif /*__ALINIX_KERNEL_GUI_CANVAS_H*/