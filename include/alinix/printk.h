/**
 * @author Ali Mirmohammad
 * @file printk.h
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
 *  - Print function util in header file for the kernel.
*/

#ifndef _ALINIX_KERNEL_PRINT_K_HEADER_H
#define _ALINIX_KERNEL_PRINT_K_HEADER_H

#include <alinix/types.h>
#include <alinix/system.h>
#include <alinix/serialport.h>
#include <alinix/enums.h>
#include <alinix/system.h>
// bool gdbEnabled = false;
// bool Initialized = false;


// static enum  ScreenMode_t screenMode = TextMode;
#include <alinix/log.h>

void Print(const char* data, uint32_t length);
void printString(const char* str);


#endif /*_ALINIX_KERNEL_PRINT_K_HEADER_H*/