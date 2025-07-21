/**
 * @author Ali Mirmohammad
 * @file colors.h
 * @credits Remco123
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
#ifndef __Novanix__GUI__COLORS_H
#define __Novanix__GUI__COLORS_H

#include <types.h>

namespace Novanix
{
    // Union describing a ARGB color in the following format:
    // 0xAARRGGBB
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
  
    class Colors
    {
    public:
        static const uint32_t Black = 0xFF000000;
        static const uint32_t White = 0xFFFFFFFF;
        static const uint32_t Red   = 0xFFFF0000;
        static const uint32_t Green = 0xFF00FF00;
        static const uint32_t Blue  = 0xFF0000FF;
        static const uint32_t Transparent = 0x00000000;
    public:
        /**
         * Blend to colors using alpha blending
         * Color1 is background
         * Color2 is foreground
        */
        static const uint32_t AlphaBlend(uint32_t color1, uint32_t color2);
        
        /**
         * Convert a ARGB color to 0xAARRGGBB format
        */
        static const uint32_t FromARGB(uint8_t a, uint8_t r, uint8_t g, uint8_t b);
    };
}

#endif