/**
 * @author Ali Mirmohammad
 * @file fat16.h
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
#ifndef __NOVANIX_KERNEL_FAT_16_DRIVER_H
#define __NOVANIX_KERNEL_FAT_16_DRIVER_H


#include <common/init.hpp>
extern struct fat16_fs novanix_fat16_fs;
extern struct block_dev my_block_device; 

struct block_dev {
    void *opaque; /* driver-specific */
    /* read `count` sectors starting at `lba` into `buf` (size: count * bytes_per_sector)
       return 0 on success, negative on error */
    int (*read_sectors)(struct block_dev *dev, u32 lba, u32 count, void *buf);
    int (*write_sectors)(struct block_dev *dev, u32 lba, u32 count, const void *buf);
};

/* -- On-disk structures (packed) -- */
struct __attribute__((packed)) bpb_common {
    u8  jmp[3];
    char oem[8];
    u16 bytes_per_sector;
    u8  sectors_per_cluster;
    u16 reserved_sector_count;
    u8  num_fats;
    u16 root_entry_count;
    u16 total_sectors_16;
    u8  media;
    u16 fat_size_16;
    u16 sectors_per_track;
    u16 num_heads;
    u32 hidden_sectors;
    u32 total_sectors_32;
    /* DOS 4.0+ extended fields follow but are not required here */
};

struct __attribute__((packed)) fat16_dir_entry {
    char     name[8];
    char     ext[3];
    u8       attr;
    u8       reserved;
    u8       ctime_tenth;
    u16      ctime;
    u16      cdate;
    u16      adate;
    u16      first_cluster_high; /* should be zero for FAT16 */
    u16      time;
    u16      date;
    u16      first_cluster_low;
    u32      file_size;
};

/* Attributes */
#define ATTR_READ_ONLY 0x01
#define ATTR_HIDDEN    0x02
#define ATTR_SYSTEM    0x04
#define ATTR_VOLNAME   0x08
#define ATTR_DIR       0x10
#define ATTR_ARCH      0x20
#define ATTR_LONG_NAME 0x0F

/* -- In-memory mount structure -- */
struct fat16_fs {
    struct block_dev *bdev;

    u16 bytes_per_sector;
    u8  sectors_per_cluster;
    u16 reserved_sector_count;
    u8  num_fats;
    u16 root_entry_count;
    u32 total_sectors;
    u16 fat_size_sectors;

    u32 first_root_dir_sector;
    u32 root_dir_sectors;
    u32 first_data_sector;
    u32 data_sectors;
    u32 total_clusters;

    /* small working buffer for sector operations (allocate by caller or kernel) */
    u8 *scratch; /* should be at least bytes_per_sector sized */
};

__always_inline INTEGER fat16_read_sector(struct fat16_fs *fs, u32 lba) {
    if (!fs) return -1; // fs is NULL
    if (!fs->bdev) return -2; // block device not set
    if (!fs->bdev->read_sectors) return -3; // no read function
    if (!fs->scratch) return -4; // no buffer allocated

    return fs->bdev->read_sectors(fs->bdev, lba, 1, fs->scratch);
}

__always_inline INTEGER fat16_parse_bpb(struct fat16_fs *fs, u32 lba0){
    
    INTEGER res = fat16_read_sector(fs,lba0);

    if (res) return res;
    struct bpb_common *bpb = (struct bpb_common *)fs->scratch;

    fs->bytes_per_sector = bpb->bytes_per_sector;
    fs->sectors_per_cluster = bpb->sectors_per_cluster;
    fs->reserved_sector_count = bpb->reserved_sector_count;
    fs->num_fats = bpb->num_fats;
    fs->root_entry_count = bpb->root_entry_count;
    fs->fat_size_sectors = bpb->fat_size_16;
    
    if (bpb->total_sectors_16 != 0)
        fs->total_sectors = bpb->total_sectors_16;
    else
        fs->total_sectors = bpb->total_sectors_32;

    fs->root_dir_sectors = ((fs->root_entry_count * 32) + (fs->bytes_per_sector - 1)) / fs->bytes_per_sector;
    fs->first_root_dir_sector = fs->reserved_sector_count + (fs->num_fats * fs->fat_size_sectors) + lba0;
    fs->first_data_sector = fs->first_root_dir_sector + fs->root_dir_sectors;

    fs->data_sectors = fs->total_sectors - (fs->reserved_sector_count + (fs->num_fats * fs->fat_size_sectors) + fs->root_dir_sectors);
    fs->total_clusters = fs->data_sectors / fs->sectors_per_cluster;

    /* basic sanity check for FAT16 cluster count range */
    if (fs->total_clusters < 4085 || fs->total_clusters >= 65525) {
        /* values indicate FAT12 or FAT32; simple driver expects FAT16-range clusters */
        /* still allow if user explicitly wants it, but warn by returning non-zero */
        /* For now, proceed but user should verify image type */
    }
    

    return 0;
}


__always_inline u32 fat16_first_sector_of_cluster(struct fat16_fs *fs,u16 cluster){
    return fs->first_data_sector + ( (u32)(cluster - 2) * fs->sectors_per_cluster );
}

__always_inline int fat16_get_fat_entry(struct fat16_fs *fs, u16 cluster, u16 *out)
{
    /* FAT starts at reserved_sector_count offset (plus lba0 assumed 0) */
    u32 fat_offset = cluster * 2; /* two bytes per FAT16 entry */
    u32 fat_sector = fs->reserved_sector_count + (fat_offset / fs->bytes_per_sector);
    u32 ent_offset = fat_offset % fs->bytes_per_sector;

    int res = fat16_read_sector(fs, fat_sector);
    if (res) return res;

    u8 *p = fs->scratch + ent_offset;
    u16 val = p[0] | (p[1] << 8);
    *out = val;
    return 0;
}

__always_inline bool fat16_is_eof(u16 cluster){
    return cluster >= 0xFFF8;
}

__always_inline INTEGER fat_16_read_cluster(struct fat16_fs *fs, u16 cluster, void *buffer){
    u32 first_sector = fat16_first_sector_of_cluster(fs, cluster);
    return fs->bdev->read_sectors(fs->bdev, first_sector, fs->sectors_per_cluster, buffer);
}

/* -- Directory and file handling structures -- */
struct fat16_dir_handle {
    struct fat16_fs *fs;
    u32 sector; /* current sector LBA in root/data area */
    u32 idx_in_sector; /* byte index within sector */
    u16 cluster; /* for subdirs (not used for root dir) */
    u32 entries_remaining;
};

struct fat16_file {
    struct fat16_fs *fs;
    u32 size;
    u16 first_cluster;
    u16 cur_cluster;
    u32 cur_pos; /* current file offset */
};


__always_inline VOID fat16_make_shortname_key(const char *name, char out[11]){
    MemoryOperations::memset(out,' ',11);

    const char* p = name;
    INTEGER i = 0;

    while (*p && *p != '.' && i < 8){
        char c = *p;
        if (c >= 'a' && c <= 'z') c -= 32;
        out[i++] = c;
        p++;
    }

    if (*p == '.'){
        p++;
        INTEGER j = 8;
        while (*p && j < 11) {
            char c = *p;
            if (c >= 'a' && c <= 'z') c -= 32;
            out[j++] = c;
            p++;
        
    }
}

}


__always_inline bool fat16_dir_entry_name_match(struct fat16_dir_entry *de, const char key[11]){
    return MemoryOperations::memcmp(de->name,key,11) == 0;
}

__always_inline INTEGER fat16_write_file(struct fat16_fs *fs, const char *filename, const void *data, u32 size){
    char short_name[11];
    fat16_make_shortname_key(filename,short_name);


    u32 root_dir_start = fs->first_root_dir_sector;
    u32 root_dir_sectors = fs->root_dir_sectors;

    for (u32 sector = 0;sector < root_dir_sectors;sector++){
        INTEGER res = fat16_read_sector(fs,root_dir_start+sector);
        if (res) return res;
        struct fat16_dir_entry *entries = (struct fat16_dir_entry *)fs->scratch;
        for (INTEGER i = 0; i < fs->bytes_per_sector / sizeof(struct fat16_dir_entry); i++){
            if (entries[i].name[0] == 0x00 || entries[i].name[0] == 0xE5){
                // Free entry found!
                u32 clusters_needed = (size + (fs->sectors_per_cluster * fs->bytes_per_sector) - 1) /
                        (fs->sectors_per_cluster * fs->bytes_per_sector);
                u16 prev_cluster = 0;
                u16 first_cluster = 0;

                for (u32 c = 0;c < clusters_needed;c++){
                    printk(VGA_RED,"No free clusters!",1);
                }
            }
        }
    }
}

INTEGER __always_inline fat16_write_sector(struct fat16_fs *fs, u32 lba, const void *buf) {
    if (!fs || !fs->bdev || !fs->bdev->write_sectors)
        return -1; // error: write not supported

    // Write exactly 1 sector to block device
    return fs->bdev->write_sectors(fs->bdev, lba, 1, buf);
}


__always_inline INTEGER fat16_write_cluster(struct fat16_fs *fs, u16 cluster, const void *data, u32 data_size){
    u32 first_sector = fat16_first_sector_of_cluster(fs,cluster);
    u32 cluster_size_bytes = fs->sectors_per_cluster * fs->bytes_per_sector;

    if (data_size > cluster_size_bytes){
        return -1;
    }
    uint8_t cluster_buf[cluster_size_bytes];
    MemoryOperations::memset(cluster_buf,0,cluster_size_bytes);
    MemoryOperations::memcpy(cluster_buf,data,data_size);
    

    for (u8 sector = 0; sector < fs->sectors_per_cluster;sector++){
        INTEGER res = fat16_write_sector(fs, first_sector + sector,
                                     cluster_buf + sector * fs->bytes_per_sector);
        if (res != 0) return res;
    }
    return 0;
}

INTEGER __always_inline write_sample_file_to_cluster_5(struct fat16_fs *fs) {
    const char sample_data[] = "HELLO FAT16";
    u16 cluster_to_use = 5; // fixed cluster number

    int res = fat16_write_cluster(fs, cluster_to_use, sample_data, sizeof(sample_data));
    return res;
}

VOID __always_inline sample_write(){
    novanix_fat16_fs.bdev = &my_block_device;
    
    uint8_t scratch_buffer[512];
    novanix_fat16_fs.scratch = scratch_buffer;
    INTEGER res = fat16_parse_bpb(&novanix_fat16_fs, 0);

    if (res != 0){
        printk(VGA_RED,"Err",1);
    }
    res = write_sample_file_to_cluster_5(&novanix_fat16_fs);
    if (res != 0) {
     printk(VGA_RED,"fail",1);
    } else {
        // success! cluster 5 now contains "HELLO FAT16"
     printk(VGA_GREEN,"success",1);

    }
}



#endif /*__NOVANIX_KERNEL_FAT_16_DRIVER_H*/