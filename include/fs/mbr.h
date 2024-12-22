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



#ifndef MBR_H
#define MBR_H

#include <types.h>


#define FAT12_SYSTEM_ID             0x1
#define FAT16_SYSTEM_ID             0x4
#define NTFS_SYSTEM_ID              0x7
#define FAT32_SYSTEM_ID             0xC //0xB



typedef struct partition {
    uint8_t bootable;
    uint8_t start_head;
    uint16_t start_sect_cyl;
    uint8_t sys_id;
    uint8_t end_head;
    uint16_t end_sect_cyl;
    uint32_t lba_start;
    uint32_t total_sectors;
} __attribute__((__packed__)) partition_t;


typedef struct mbr {
    uint8_t fill[436];
    uint8_t id[10];
    partition_t partition_table[4];
    uint8_t signature[2];
} __attribute__((__packed__)) mbr_t;



#endif // MBR_H