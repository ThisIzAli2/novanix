/**
 * @author Ali Mirmohammad
 * @file fat32.cpp
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

#include <fs/fat32.h>

extern fat32_fs_t fs;
#define SECTOR_SIZE 512
extern uint8_t *disk_image;   // pointer to disk image in memory
extern uint64_t disk_image_size;

static INTEGER __always_inline fat32_cluster_to_lba(uint32_t cluster,fat32_fs_t *fs){
    return fs->data_start_lba + (cluster-2) * fs->sectors_per_cluster;
}

uint32_t static __always_inline fat32_get_fat_entry(uint32_t cluster, fat32_fs_t *fs){
    uint32_t fat_offset = cluster *4;
    uint32_t fat_sector = fs->fat_start_lba + (fat_offset / fs->bytes_per_sector);
    uint32_t ent_offset = fat_offset % fs->bytes_per_sector;

    uint8_t sector[512];
    block_device_read_sector(fat_sector, sector);

    uint32_t entry = *(uint32_t*)&sector[ent_offset];
    return entry & 0x0FFFFFFF; // mask 28 bits
}

int fat32_mount(uint32_t partition_lba) {
    uint8_t sector[512];
    if (block_device_read_sector(partition_lba, sector) != 0) return -1;

    MemoryOperations::memcpy(&fs.bpb, sector, sizeof(fat32_bpb_t));
    fs.bytes_per_sector = fs.bpb.bytes_per_sector;
    fs.sectors_per_cluster = fs.bpb.sectors_per_cluster;
    fs.num_fats = fs.bpb.num_fats;
    fs.fat_start_lba = partition_lba + fs.bpb.reserved_sector_count;
    fs.data_start_lba = fs.fat_start_lba + fs.num_fats * fs.bpb.fat_size_32;
    fs.root_cluster = fs.bpb.root_cluster;

    return 0;
}

VOID fat32_list_directory(uint32_t cluster) {
    uint32_t current = cluster;
    uint8_t sector[512];
    while (current < 0x0FFFFFF8) {
        uint32_t first_sector = fat32_cluster_to_lba(current, &fs);
        for (int i = 0; i < fs.sectors_per_cluster; i++) {
            block_device_read_sector(first_sector + i, sector);
            for (int offset = 0; offset < fs.bytes_per_sector; offset += 32) {
                fat32_dir_entry_t* entry = (fat32_dir_entry_t*)&sector[offset];
                if (entry->name[0] == 0x00) return; // no more entries
                if (entry->name[0] == 0xE5) continue; // deleted
                if (entry->attr == 0x0F) continue; // LFN, skip for now

                char name[12];
                MemoryOperations::memcpy(name, entry->name, 11);
                name[11] = 0;
                // Trim spaces in name here...

                // Print or process file name
                printk(VGA_WHITE,"File: %s Size: %u\n",1, name, entry->file_size);
            }
        }
        current = fat32_get_fat_entry(current, &fs);
    }
}



INTEGER block_device_read_sector(uint32_t lba, uint8_t *buffer) {
    uint64_t offset = (uint64_t)lba * SECTOR_SIZE;
    if (offset + SECTOR_SIZE > disk_image_size) {
        return -1; // out of range
    }
    MemoryOperations::memcpy(buffer, disk_image + offset, SECTOR_SIZE);
    return 0; // success
}
