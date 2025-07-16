/**
 * @author Ali Mirmohammad
 * @file textgui.h
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
#ifndef __Novanix__INSTALLER__TEXTGUI_H
#define __Novanix__INSTALLER__TEXTGUI_H

#include <system/bootconsole.h>

namespace Novanix
{
    #define TEXT_COLOR system::VGA_COLOR_WHITE

    //Draw a simple gui using the VGA text mode
    class TextGUI
    {
    public:
        static void DisableCursor();
        static void SetPixel(int x, int y, char color, common::uint16_t character = ' ', char background = system::VGA_COLOR_BLUE);
        static void ClearScreen(char color = system::VGA_COLOR_BLACK);
        static void StatusBar(char* text, int percentage = 0);
        static void DrawString(char* text, int x, int y, char color = TEXT_COLOR, char background = system::VGA_COLOR_BLUE);
    };
}

#endif