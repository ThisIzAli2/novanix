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

/**
 * @abstraction:
 *  - Kernel device for file system implementation.
*/

#ifndef DEVICE_H
#define DEVICE_H

#include <fs/vfs.h>
#include <fs/fat_mount.h>

typedef struct device {
    int id;
    int type; // 0 floppy, 1 ata hdd
    char mount[4];
    char* (*read) (int lba);
    int (*write) (int lba);
    filesystem fs;
    fat_mount_info_t minfo;
} device_t;

void device_register(device_t *dev);
device_t *get_dev_by_name(char *name);
device_t *get_dev_by_id(int id);
int get_dev_id_by_name(char *name);

#endif