/**
 * @author Ali Mirmohammad
 * @file fontparser.cpp
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
#include <gui/fonts/fontparser.h>
#include <vfs.h>
#include <string.h>
#include <log.h>


using namespace Novanix;

Font* FontParser::FromFile(char* filename)
{
    if(FileExists(filename) == false)
        return 0;

    uint32_t fileSize = GetFileSize(filename);
    if((int)fileSize == -1)
        return 0;

    uint8_t* filebuffer = new uint8_t[fileSize];
    if(ReadFile(filename, filebuffer) != 0) {
        delete filebuffer;
        return 0;
    }


    // Place CFF header over buffer
    CFFHeader* header = (CFFHeader*)filebuffer;
    if(header->Magic != 0xCFF || header->Version != 1) {
        delete filebuffer;
        return 0;
    }
    
    Print("Parsing font %s, size = %d Points\n", (char*)(filebuffer + header->FontNameOffset), header->FontSize);
    
    Font* result = new Font();
    result->data = filebuffer;
    result->name = (char*)(filebuffer + header->FontNameOffset);
    result->offsetTable = header->CharacterOffsets;
    result->size = header->FontSize;

    return result;
}