/**
 * @author Ali Mirmohammad
 * @file ntfs.h
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

#ifndef __NOVANIX_KERNEL_NTFS_H__FS
#define __NOVANIX_KERNEL_NTFS_H__FS


#include <common/types.h>
#include <typing.hpp>

using namespace Novanix::common;

typedef struct ntfs_file {
    uint64_t mft_entry_number;
    uint64_t size;
    uint32_t cluster_count;
    uint32_t* clusters;
    uint16_t flags;
}ntfs_file_t;


typedef struct ntfs_volume {
    uint32_t cluster_size;
    uint64_t total_clusters;
    uint64_t mft_start_lcn;  // logical cluster number
} ntfs_volume_t;

typedef struct ntfs_mft_entry {
    uint64_t entry_number;
    uint16_t flags;      // file/directory
    uint64_t size;
    uint32_t *clusters;  // list of clusters holding data
} ntfs_mft_entry_t;

VOID ntfs_mount(uint8_t* boot_sector,ntfs_file_t*vol);
int ntfs_read_file(ntfs_file_t *file, uint8_t *buffer, uint64_t length);

#endif /*__NOVANIX_KERNEL_NTFS_H__FS*/
