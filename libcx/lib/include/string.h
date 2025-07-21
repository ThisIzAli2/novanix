/**
 * @author Ali Mirmohammad
 * @file string.h
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
#ifndef __NovanixLIB__MEMORYOPERATIONS_H
#define __NovanixLIB__MEMORYOPERATIONS_H

#include <stddef.h>
#include <list.h>

extern "C"
{
    int memcmp(const void* aptr, const void* bptr, size_t size);
    void* memcpy(void* __restrict__ dstptr, const void* __restrict__ srcptr, size_t size);
    void* memmove(void* dstptr, const void* srcptr, size_t size);
    void* memset(void* bufptr, int value, size_t size);
    size_t strlen(const char* str);
    int strcmp(const char *s1, const char *s2);
   
    int str_IndexOf(const char* str, char c, int skip = 0);
    bool str_Contains(const char* str, char c);
    List<char*> str_Split(const char* str, char d);
    char* str_Uppercase(char* str);
    char* str_Lowercase(char* str);
    char* str_Add(char* str, char c);
    char* str_Combine(char* part1, char* part2);

    bool isvalid(unsigned char key);
}

#endif