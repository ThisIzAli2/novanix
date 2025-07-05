/**
 * @author Ali Mirmohammad
 * @file clean.h
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
#ifndef __NOVANIX_KERNEL_CLEAN_H
#define __NOVANIX_KERNEL_CLEAN_H

#define VGA_ADDRESS 0xB8000
#define VGA_COLUMNS 80
#define VGA_ROWS 25
#define WHITE_ON_BLACK 0x0F

void inline clear_screen() {
    unsigned char* video_memory = (unsigned char*) VGA_ADDRESS;
    for (int i = 0; i < VGA_COLUMNS * VGA_ROWS; i++) {
        video_memory[i * 2] = ' ';               // Blank character
        video_memory[i * 2 + 1] = WHITE_ON_BLACK; // Attribute
    }
}

#endif