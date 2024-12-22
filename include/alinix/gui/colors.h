/**
 * @author Ali Mirmohammad
 * @file colors.h
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
#ifndef __ALINIX_KERNEL_GUI_COLORS_H
#define __ALINIX_KERNEL_GUI_COLORS_H

#include <alinix/types.h>


typedef union Color4Tag
{
    uint32_t c;
    struct ColorComponents
    {
        uint8_t b;
        uint8_t g;
        uint8_t r;
        uint8_t a;
    } argb;
} Color4;


static const uint32_t Transparent = 0x00000000;
static const uint32_t Black = 0xFF000000;
static const uint32_t White = 0xFFFFFFFF;
static const uint32_t Red   = 0xFFFF0000;
static const uint32_t Green = 0xFF00FF00;
static const uint32_t Blue  = 0xFF0000FF;

const uint32_t AlphaBlend(uint32_t color1, uint32_t color2);
#endif /*__ALINIX_KERNEL_GUI_COLORS_H*/