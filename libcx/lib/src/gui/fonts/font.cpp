/**
 * @author Ali Mirmohammad
 * @file font.cpp
 * Credits Remco123
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
#include <gui/fonts/font.h>

using namespace Novanix;

void Font::BoundingBox(char* string, int* retW, int* retH)
{
    if(string == 0 || retW == 0 || retH == 0)
        return; // Error with arguments

    if(this->data == 0)
        return; // Not initialized
    
    // Reset variables
    *retW = 0;
    *retH = 0;
    

    int xOffset = 0;
    int yOffset = 0;
    while(*string)
    {
        // Get the character we need to draw for this string
        char c = *string++;

        // Set initial values for first character
        if(xOffset == 0 && yOffset == 0)
            yOffset = ((uint8_t*)(this->data + this->offsetTable[0]))[1];

        // Check for newline
        if(c == '\n') {
            if(xOffset > *retW)
                *retW = xOffset;
            
            xOffset = 0;

            // Add the height of the space character. TODO: Update this!
            yOffset += ((uint8_t*)(this->data + this->offsetTable[0]))[1] + 1;
            continue;
        }

        // Load data for this char from the font
        const uint8_t* charData = (uint8_t*)(this->data + this->offsetTable[(int)c - 32]);
        xOffset += charData[0];
    }

    // Update return values
    // retW might already be correctly set by another line of text
    if(xOffset > *retW)
        *retW = xOffset;
    
    *retH = yOffset;
}