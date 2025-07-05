/**
 * @author Ali Mirmohammad
 * @file file.h
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
#ifndef __NOVA_KERNEL_FILE_H
#define __NOVA_KERNEL_FILE_H

#define MAX_FILES 8
#define MAX_FILE_SIZE 4096
#define MAX_FILENAME_LEN 64



typedef struct {
    char name[MAX_FILENAME_LEN];
    char content[MAX_FILE_SIZE];
    int size;
    int cursor;
    int used;
} File;

int open(const char* filename, int flags);
int read(int fd, char* buf, int size);
int write(int fd, const char* buf, int size);
int close(int fd);
void init_filesystem();

#define O_RDONLY 0x01
#define O_WRONLY 0x02
#define O_CREAT  0x04




#endif // __NOVA_KERNEL_FILE_H