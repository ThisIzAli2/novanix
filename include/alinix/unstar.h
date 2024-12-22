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
 * @file unstar.h
 * @abstract:
 *  - Kernel TAR file and ZIP implementation header file.
*/
#ifndef __ALINIX_KERNEL_UNSTAR_H
#define __ALINIX_KERNEL_UNSTAR_H

/**
 * @brief Function for the TAR file system.
*/
int oct2bin(unsigned char *str, int size);

/*Returns the size and the pointer to the file data*/
int tar_lookup(unsigned char *archive, char *filename, char **out);

/**
 * @brief Getting TAR file name.
*/
char* getTarFileName(unsigned char* archive);
#define TAR_FILENAME_OFFSET 0
#define TAR_FILENAME_SIZE   100
#define TAR_HEADER_SIZE 512

/**
 * @brief TAR implementation for the kernel file system.
*/
void removeFileFromTar(char* fileName,unsigned char *archive,unsigned char* fileToRemove,uint32_t size);
#endif /* __ALINIX_KERNEL_UNSTAR_H */