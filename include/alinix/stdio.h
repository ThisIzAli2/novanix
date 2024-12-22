/**
 * @author Ali Mirmohammad
 * @file stdio.h
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
 *  - Kernel I/O operations implementation header file.
*/
#ifndef __ALINIX_KERNEL_STDIO_H
#define __ALINIX_KERNEL_STDIO_H




typedef struct {
    char *dummy[1];
}FILE;
int fprintf(FILE * file, const char *format, ...);


#define UACPI_ALIGN_UP_MASK(x, mask) (((x) + (mask)) & ~(mask))
#define UACPI_ALIGN_UP(x, val, type) UACPI_ALIGN_UP_MASK(x, (type)(val) - 1)


#endif /*__ALINIX_KERNEL_STDIO_H*/