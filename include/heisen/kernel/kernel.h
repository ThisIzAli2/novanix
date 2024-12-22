#ifndef _HEISEN_KERNEL_INCLUDE_KERNEL_H
#define _HEISEN_KERNEL_INCLUDE_KERNEL_H

#include <heisen/typing.h>

#define OS_VERSION_MINOR 0
#define OS_VERSION_MONTHLY 3
#define OS_VERSION_NUM 1

#define MAX_DISK 4

typedef struct disk_info_t {
    uint id;
    char name[4];
    char desc[32];
    uint  fstype;      // File system type: see ulib.h
    uint  fssize;      // Number of blocks in file system
    uint  sectors;
    uint  sides;
    uint  cylinders;
    uint  size;        // Disk size (MB)
    bool  isATA;

}disk_info_t;


extern disk_info_t disk_info[MAX_DISK];
extern uint8_t system_disk; // System disk

#endif // _HEISEN_KERNEL_INCLUDE_KERNEL_H