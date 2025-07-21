/**
 * @author Ali Mirmohammad
 * @file fontparser.h
 * @Credits Remco123
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
#ifndef __Novanix__GUI__FONTS__FONTPARSER_H
#define __Novanix__GUI__FONTS__FONTPARSER_H

#include <types.h>
#include <gui/fonts/font.h>

namespace Novanix
{
    // Header of a Novanix Font File (CFF)
    struct CFFHeader
    {
        uint32_t Magic;                     // Magic number containing 0xCFF
        uint8_t  Version;                   // Version of this font file, propably 1
        uint16_t FontSize;                  // Size of font in dots
        uint32_t FontNameOffset;            // Offset in file data where font name is stored

        uint32_t CharacterOffsets[127-32];  // Table which contains offsets to the data for each character
    } __attribute__((packed));

    class FontParser
    {
    public:
        static Font* FromFile(char* filename);
    };
}

#endif