/**
 * @author Ali Mirmohammad
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
 * @file convert.h
 * Abstraction
 *      - Provide utility for converting number (hex,decimal,binary) to each other
*/

#ifndef __ALINIX_KERNEL_CONVERT_HEADER_H
#define __ALINIX_KERNEL_CONVERT_HEADER_H

#include <alinix/types.h>

int isSpace(char c);

char* IntToString(int n);

char*IntToString32(uint32_t n);

char* IntToHexString(uint8_t w);

int StringToInt(char* string);

uint32_t HexToInt(char* string);

#endif /*__ALINIX_KERNEL_CONVERT_HEADER_H*/