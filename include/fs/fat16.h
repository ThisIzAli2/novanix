#ifndef __NOVANIX_KERNEL_FAT_16_DRIVER_H
#define __NOVANIX_KERNEL_FAT_16_DRIVER_H


#include <common/init.hpp>

struct block_dev {
    void *opaque; /* driver-specific */
    /* read `count` sectors starting at `lba` into `buf` (size: count * bytes_per_sector)
       return 0 on success, negative on error */
    int (*read_sectors)(struct block_dev *dev, u32 lba, u32 count, void *buf);
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

__always_inline INTEGER fat16_read_sector(struct fat16_fs *fs,u32 lba){
    return fs->bdev->read_sectors(fs->bdev,lba,1,fs->scratch);
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


#endif /*__NOVANIX_KERNEL_FAT_16_DRIVER_H*/