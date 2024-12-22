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

#ifndef FAT12_MOUNT_H
#define FAT12_MOUNT_H

#include <types.h>

typedef struct fat_mount_info {
    /* FS type
     * 0 = FAT12
     * 1 = FAT16
     * 2 = FAT32
     * 3 = EXFAT
     */
    int type;
    uint32_t n_sectors;
    uint32_t fat_offset;
    uint32_t n_root_entries;
    uint32_t root_offset;
    uint32_t root_size;
    uint32_t fat_size;
    uint32_t fat_entry_size;
    uint32_t first_data_sector;
    uint32_t data_sectors;
} fat_mount_info_t;

#endif