/**
 * @author Ali Mirmohammad
 * @file font.h
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
#ifndef __Novanix__GUI__FONTS__FONT_H
#define __Novanix__GUI__FONTS__FONT_H

#include <types.h>

namespace Novanix
{
    struct Font
    {
        uint8_t* data           = 0; // Raw font data including header
        char* name              = 0; // Name of this font, stored inside data buffer
        int size                = 0; // Size of this font in points
        uint32_t* offsetTable   = 0; // Offsets for each character data sorted by character

        void BoundingBox(char* str, int* retW, int* retH);
    };
}

#endif