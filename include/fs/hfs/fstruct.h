/**
 * @author Ali Mirmohammad
 * @file fstruct.h
 * @credits Remco123
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
#ifndef __NOVANIX_KERNEL_HFS_FILE__STRUCTURE_H
#define __NOVANIX_KERNEL_HFS_FILE__STRUCTURE_H

#include <fs/diskio.h>

typedef struct {
    char signature[2]; // 'H','+'
    uint16_t version;
    uint32_t catalogFileStart;
    uint32_t catalogFileLength;
    uint32_t allocationFileStart;
    uint32_t allocationFileLength;
    uint32_t blockSize;
    uint32_t totalBlocks;
    uint32_t freeBlocks;
} hfs_volume_header_t;

typedef struct {
    uint32_t startBlock;
    uint32_t blockCount;
} hfs_extent_t;

typedef struct {
    uint32_t fileID;
    uint32_t parentID;
    char name[255];
    uint32_t dataStartBlock;
    uint32_t dataLength;
} hfs_catalog_file_t;

VOID hfs_mount();

#endif /*__NOVANIX_KERNEL_HFS_FILE__STRUCTURE_H*/