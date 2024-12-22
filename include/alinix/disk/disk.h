/**
 * @file disk.h
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
 *  - Kernel DISK driver implementation.
*/
#ifndef __ALINIX_KERNEL_DISK_H
#define __ALINIX_KERNEL_DISK_H

#include <alinix/types.h>
#include <alinix/ulib.h>

// typedef enum {
//     DISK_TYPE_UNKNOWN,
//     DISK_TYPE_HDD,
//     DISK_TYPE_SSD
// } DiskType;

// typedef struct {
//     void* controller; // Which controller is controlling this disk device
//     uint32_t controllerIndex; // The real number for the disk on the controller
//     char* identifier; // Disk Identifier
//     DiskType type; // Type of disk
//     uint64_t size; // Size of disk in bytes
//     uint32_t numBlocks; // Number of data blocks
//     uint32_t blockSize; // Size of one block of data
// } Disk;

// Disk* Disk_create(uint32_t controllerIndex, void* controller, DiskType type, uint64_t size, uint32_t blocks, uint32_t blocksize) {
//     Disk* disk = (Disk*)malloc(sizeof(Disk));
//     disk->controllerIndex = controllerIndex;
//     disk->controller = controller;
//     disk->type = type;
//     disk->size = size;
//     disk->numBlocks = blocks;
//     disk->blockSize = blocksize;
//     disk->identifier = NULL; // Allocate and set identifier if needed
//     return disk;
// }

char Disk_ReadSector(Disk* disk, uint32_t lba, uint8_t* buf) {
    // Implement ReadSector function
    return 0;
}

char Disk_WriteSector(Disk* disk, uint32_t lba, uint8_t* buf) {
    // Implement WriteSector function
    return 0;
}

#endif /*__ALINIX_KERNEL_DISK_H*/