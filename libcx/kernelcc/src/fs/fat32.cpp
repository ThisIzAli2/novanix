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

/**
 * @brief Converts a FAT32 cluster number to its corresponding Logical Block Address (LBA).
 * 
 * In the FAT32 file system, files are organized in clusters, each consisting of multiple sectors.
 * This function calculates the starting sector (LBA) of a given cluster number.
 * 
 * Clusters are numbered starting from 2, as clusters 0 and 1 are reserved.
 * The calculation returns the LBA of the first sector of the specified cluster.
 * 
 * @param cluster The FAT32 cluster number to convert. Must be >= 2.
 * @param fs Pointer to a FAT32 filesystem metadata structure containing:
 *           - data_start_lba: LBA of the first data sector in the partition.
 *           - sectors_per_cluster: Number of sectors per cluster.
 * 
 * @return INTEGER The Logical Block Address (sector number) corresponding to the cluster start.
 * 
 * @note This function is marked as `static` and `__always_inline` for performance.
 * 
 * @example
 * fat32_fs_t fat32_fs = {2048, 8}; // data starts at sector 2048, 8 sectors per cluster
 * uint32_t cluster_num = 5;
 * INTEGER sector = fat32_cluster_to_lba(cluster_num, &fat32_fs);
 * // sector = 2048 + (5 - 2) * 8 = 2072
 */
static INTEGER __always_inline fat32_cluster_to_lba(uint32_t cluster,fat32_fs_t *fs){
    return fs->data_start_lba + (cluster-2) * fs->sectors_per_cluster;
}

/**
 * @brief Retrieves the FAT32 File Allocation Table (FAT) entry for a given cluster.
 * 
 * In the FAT32 filesystem, the FAT is an array of 32-bit entries, each corresponding 
 * to a cluster. This function reads the FAT entry for the specified cluster to 
 * determine the status or next cluster in the chain.
 * 
 * FAT32 entries use only the lower 28 bits; the upper 4 bits are reserved.
 * 
 * @param cluster The cluster number for which to retrieve the FAT entry.
 * @param fs Pointer to the FAT32 filesystem metadata structure, which includes:
 *           - fat_start_lba: LBA of the first FAT sector.
 *           - bytes_per_sector: Number of bytes in one sector.
 * 
 * @return uint32_t The 28-bit FAT entry value, indicating the next cluster number 
 *                  in the chain or a special marker (e.g., end-of-chain).
 * 
 * @details
 * The function calculates the byte offset of the FAT entry:
 * - Each FAT entry is 4 bytes (32 bits).
 * - The FAT sector containing the entry is determined by dividing the offset by the sector size.
 * - The offset within that sector is found by modulo operation.
 * 
 * The sector containing the FAT entry is read into a buffer,
 * and the 4-byte FAT entry is extracted and masked to 28 bits.
 * 
 * @note 
 * - This function assumes `block_device_read_sector` is available and works correctly.
 * - The FAT is assumed to be contiguous and not fragmented.
 * - This function is declared `static` and `__always_inline` for efficiency.
 * 
 * @example
 * fat32_fs_t fs = {
 *     .fat_start_lba = 1000,
 *     .bytes_per_sector = 512
 * };
 * uint32_t cluster = 5;
 * uint32_t next_cluster = fat32_get_fat_entry(cluster, &fs);
 */
uint32_t static __always_inline fat32_get_fat_entry(uint32_t cluster, fat32_fs_t *fs){
    uint32_t fat_offset = cluster *4;
    uint32_t fat_sector = fs->fat_start_lba + (fat_offset / fs->bytes_per_sector);
    uint32_t ent_offset = fat_offset % fs->bytes_per_sector;

    uint8_t sector[512];
    block_device_read_sector(fat_sector, sector);

    uint32_t entry = *(uint32_t*)&sector[ent_offset];
    return entry & 0x0FFFFFFF; // mask 28 bits
}


/**
 * @brief Mounts a FAT32 filesystem by reading and parsing its BIOS Parameter Block (BPB).
 * 
 * This function initializes the FAT32 filesystem metadata structure (`fs`) 
 * by reading the first sector of the specified partition (usually the boot sector)
 * and extracting essential filesystem parameters from the BIOS Parameter Block (BPB).
 * 
 * It calculates key filesystem locations such as the FAT start sector and data region start sector,
 * enabling subsequent file system operations like cluster-to-LBA translation.
 * 
 * @param partition_lba The Logical Block Address (LBA) of the partition's start sector (usually the boot sector).
 * 
 * @return INTEGER Returns 0 on success, or -1 if the initial sector read fails.
 * 
 * @details
 * The function performs the following steps:
 * 1. Reads the sector at `partition_lba` into a buffer.
 * 2. Copies the BPB structure from the buffer into `fs.bpb`.
 * 3. Extracts parameters such as bytes per sector, sectors per cluster, number of FATs.
 * 4. Calculates:
 *    - `fs.fat_start_lba`: The LBA where the FAT begins (partition start + reserved sectors).
 *    - `fs.data_start_lba`: The LBA where the data region begins (FAT start + FAT area size).
 *    - `fs.root_cluster`: The cluster number of the root directory.
 * 
 * These parameters are critical for navigating and reading files on the FAT32 filesystem.
 * 
 * @note
 * - Assumes `block_device_read_sector` reads 512-byte sectors from the device.
 * - Assumes `MemoryOperations::memcpy` is available for memory copying.
 * - The `fs` object is a global or accessible FAT32 filesystem state structure.
 * 
 * @example
 * uint32_t partition_start = 2048; // Example partition start sector
 * if (fat32_mount(partition_start) != 0) {
 *     // Handle error
 * }
 */
INTEGER fat32_mount(uint32_t partition_lba) {
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

/**
 * @brief Lists all directory entries starting from a given FAT32 cluster.
 * 
 * This function traverses the FAT32 cluster chain beginning at the specified cluster,
 * reading each sector in each cluster, and processes directory entries found therein.
 * It skips deleted entries, long file name (LFN) entries, and stops at the end of directory entries.
 * 
 * The function prints the file name and size for each valid directory entry.
 * 
 * @param cluster The starting cluster number of the directory to list.
 * 
 * @return OID No explicit return value (void-equivalent). The function returns early
 *             when the end of the directory entries is reached.
 * 
 * @details
 * - Uses `fat32_cluster_to_lba` to convert cluster numbers to LBAs.
 * - Reads sectors cluster-by-cluster.
 * - Each directory entry is 32 bytes.
 * - Handles FAT32 special cluster markers to detect the end of cluster chain.
 * - Skips:
 *    - Entries with first byte 0x00 (no more entries).
 *    - Entries with first byte 0xE5 (deleted files).
 *    - Entries with attribute 0x0F (Long File Name entries).
 * - Copies file names from the directory entry, trimming spaces may be needed.
 * - Uses `printk` to output file information (file name and file size).
 * 
 * @note
 * - Assumes `block_device_read_sector` reads a sector from the block device.
 * - Assumes `fat32_get_fat_entry` provides the next cluster in the FAT chain.
 * - Assumes `MemoryOperations::memcpy` is available for copying data.
 * - Assumes `fs` is a global or accessible FAT32 filesystem metadata structure.
 * 
 * @example
 * uint32_t root_dir_cluster = fs.root_cluster;
 * fat32_list_directory(root_dir_cluster);
 */
VOID fat32_list_directory(uint32_t cluster) {
    uint32_t current = cluster;
    uint8_t sector[512];
    while (current < 0x0FFFFFF8) {
        uint32_t first_sector = fat32_cluster_to_lba(current, &fs);
        for (INTEGER i = 0; i < fs.sectors_per_cluster; i++) {
            block_device_read_sector(first_sector + i, sector);
            for (INTEGER offset = 0; offset < fs.bytes_per_sector; offset += 32) {
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


/**
 * @brief Reads a 512-byte sector from a block device image into a buffer.
 * 
 * This function simulates reading a disk sector by copying data from a disk image
 * loaded in memory. It calculates the byte offset of the requested Logical Block Address (LBA)
 * sector within the disk image and copies 512 bytes into the provided buffer.
 * 
 * @param lba The Logical Block Address (sector number) to read.
 * @param buffer Pointer to a buffer of at least 512 bytes where the sector data will be copied.
 * 
 * @return INTEGER Returns 0 on success, or -1 if the requested sector is out of the disk image bounds.
 * 
 * @details
 * - Assumes a sector size of 512 bytes (SECTOR_SIZE).
 * - Checks that the requested sector lies within the range of the disk image size.
 * - Copies sector data from `disk_image` (assumed to be a pointer to loaded disk image bytes).
 * 
 * @note
 * - This function operates on an in-memory disk image, not on physical hardware.
 * - `disk_image_size` must represent the total size in bytes of the disk image.
 * - `MemoryOperations::memcpy` is used for copying data safely.
 * 
 * @example
 * uint8_t buffer[512];
 * if (block_device_read_sector(2048, buffer) != 0) {
 *     // Handle read error
 * }
 */
INTEGER block_device_read_sector(uint32_t lba, uint8_t *buffer) {
    uint64_t offset = (uint64_t)lba * SECTOR_SIZE;
    if (offset + SECTOR_SIZE > disk_image_size) {
        return -1; // out of range
    }
    MemoryOperations::memcpy(buffer, disk_image + offset, SECTOR_SIZE);
    return 0; // success
}
