/**
 * @author Ali Mirmohammad
 * @file string.h
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
 *  - Kernel string operations implementation in header file.
*/
#ifndef __ALINIX_KERNEL_STRING_H
#define __ALINIX_KERNEL_STRING_H

#include <alinix/types.h>

#define _U 0x01 // Upper case letter mask
#define _L 0x02 // Lower case letter mask

#define isalpha(c)  (((c) >= 'A' && (c) <= 'Z') || ((c) >= 'a' && (c) <= 'z'))
int strlen(const char* str);
bool strcmp(const char* strA, const char* strB);
bool strncmp(const char* s1, const char* s2, int n);
int IndexOf(const char* str, char c, uint32_t skip);

char* Uppercase(char* str);
char* Lowercase(char* str);
char* strcpy(char *s1, const char *s2);
char* strncpy(char *s1, const char *s2, unsigned int n);
char *strcat(char *dst, const char *src);

#endif /*__ALINIX_KERNEL_STRING_H*/