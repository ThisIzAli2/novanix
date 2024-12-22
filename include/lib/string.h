/**
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

#ifndef STRING_H
#define STRING_H

#include "../types.h"

void strcpy(char *str, char *format);
void strncpy(char *str, char *format, size_t len);
int strcmp(char *str1, char *str2);
int strncmp(char *str1, char *str2, size_t len);
void memset(void *start, uint32_t val, size_t len);
void memcpy(void *dest, void *src, int size);
void itoa(int val, char *str, int base);
int atoi(char *str);
int strlen(char *str);
char char_at(char *str, int pos);
void to_uppercase(char *str, char *format);
void to_lowercase(char *str, char *format);
char toupper(char c);
char tolower(char c);
int vsprintf(char *str, char *format, va_list args);
char *strchr(char *str, int c);
char *strcat(char *dest, char *src);

#endif