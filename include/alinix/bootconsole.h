/**
 * @author Ali Mirmohammad
 * @file bootconsole.h
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
 *  - Kernel boot console implemented.
*/
#ifndef __ALINIX_KERNEL_BOOT_CONSOLE_H
#define __ALINIX_KERNEL_BOOT_CONSOLE_H

#include <alinix/types.h>

// int XOffset;
// int YOffset;
// bool writeToSerial = false;

void Scroll();

#define VGA_WIDTH 80
#define VGA_HEIGHT 25

// uint8_t ForegroundColor;
// uint8_t BackgroundColor;

void ConsoleInit(bool enableSerial) ;


void Write(char* str) ;

void WriteLine(char* str);


void ConsoleClear();

void SetX(int x);

void SetY(int y);

uint16_t* GetBuffer();



/////////////////////////////////////////////////////
enum vga_color {
    VGA_COLOR_BLACK = 0,
    VGA_COLOR_BLUE = 1,
    VGA_COLOR_GREEN = 2,
    VGA_COLOR_CYAN = 3,
    VGA_COLOR_RED = 4,
    VGA_COLOR_MAGENTA = 5,
    VGA_COLOR_BROWN = 6,
    VGA_COLOR_LIGHT_GREY = 7,
    VGA_COLOR_DARK_GREY = 8,
    VGA_COLOR_LIGHT_BLUE = 9,
    VGA_COLOR_LIGHT_GREEN = 10,
    VGA_COLOR_LIGHT_CYAN = 11,
    VGA_COLOR_LIGHT_RED = 12,
    VGA_COLOR_LIGHT_MAGENTA = 13,
    VGA_COLOR_LIGHT_BROWN = 14,
    VGA_COLOR_WHITE = 15
};

static uint8_t BackgroundColor = VGA_COLOR_BLACK; //Default console background color
static uint8_t ForegroundColor = VGA_COLOR_WHITE; //Default console foreground color


#endif /*__ALINIX_KERNEL_BOOT_CONSOLE_H*/