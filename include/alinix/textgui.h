/**
 * @author Ali Mirmohammad
 * @author Ali Mirmohammad
 * @file textgui.h
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
 * @abstraction:
 *  - Kernel Textgui implementation.
*/
#ifndef __ALINIX_KERNEL_TEXTGUI_H
#define __ALINIX_KERNEL_TEXTGUI_H

#include <alinix/bootconsole.h>
#include <alinix/enums.h>
#include <alinix/types.h>


#define TEXT_COLOR VGA_COLOR_WHITE

void DisableCursor(); // Disables the cursor of the GUI interface
void SetPixel(int x, int y, char color,uint16_t character, char background); // Sets the pixels of the kernel GUI.
void ClearScreen(char color );  // Clear the Screen 
void StatusBar(char* text, int percentage); // Kernel Status bar progress
void TextDrawString(char* text, int x, int y, char color, char background); // Draws the string of the kernel.

#endif /*__ALINIX_KERNEL_TEXTGUI_H*/