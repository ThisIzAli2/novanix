/**
 * @author Ali Mirmohammad
 * @file fat32.h
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
#ifndef __NOVANIX_KERNEL_FILE_SYSTEM__FAT_32__H
#define __NOVANIX_KERNEL_FILE_SYSTEM__FAT_32__H


#include <common/init.hpp>

typedef struct {
    fat32_bpb_t bpb;
    uint32_t fat_start_lba;
    uint32_t data_start_lba;
    uint32_t root_cluster;
    uint16_t bytes_per_sector;
    uint8_t sectors_per_cluster;
    uint8_t num_fats;
} fat32_fs_t;


typedef struct __attribute__((packed)) {
    uint8_t  jump_boot[3];
    uint8_t  oem_name[8];
    uint16_t bytes_per_sector;
    uint8_t  sectors_per_cluster;
    uint16_t reserved_sector_count;
    uint8_t  num_fats;
    uint16_t root_entry_count;    // usually 0 for FAT32
    uint16_t total_sectors_16;
    uint8_t  media;
    uint16_t fat_size_16;         // FAT16 size, 0 for FAT32
    uint16_t sectors_per_track;
    uint16_t num_heads;
    uint32_t hidden_sectors;
    uint32_t total_sectors_32;

    // FAT32 extended BPB
    uint32_t fat_size_32;
    uint16_t ext_flags;
    uint16_t fs_version;
    uint32_t root_cluster;
    uint16_t fs_info;
    uint16_t backup_boot_sector;
    uint8_t  reserved[12];
    uint8_t  drive_number;
    uint8_t  reserved1;
    uint8_t  boot_signature;
    uint32_t volume_id;
    uint8_t  volume_label[11];
    uint8_t  fs_type[8];
} fat32_bpb_t;

// Directory entry structure (short name)
typedef struct __attribute__((packed)) {
    uint8_t  name[11];
    uint8_t  attr;
    uint8_t  nt_reserved;
    uint8_t  creation_time_tenth;
    uint16_t creation_time;
    uint16_t creation_date;
    uint16_t last_access_date;
    uint16_t first_cluster_high;
    uint16_t write_time;
    uint16_t write_date;
    uint16_t first_cluster_low;
    uint32_t file_size;
} fat32_dir_entry_t;


INTEGER block_device_read_sector(uint32_t lba, uint8_t* buffer);
INTEGER block_device_write_sector(uint32_t lba, const uint8_t* buffer);
INTEGER fat32_mount(uint32_t partition_lba);
void fat32_list_directory(uint32_t cluster);


#endif /*__NOVANIX_KERNEL_FILE_SYSTEM__FAT_32__H*/