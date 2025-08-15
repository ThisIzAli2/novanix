/**
 * @author Ali Mirmohammad
 * @file hfs.h
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
#ifndef __NOVANIX_KERNEL_HFS_HFS_H
#define __NOVANIX_KERNEL_HFS_HFS_H

#include <global.h>
#include <common/init.hpp>


VOID hfs_read_block(uint32_t block_num, uint8_t* buffer);
VOID hfs_write_block(uint32_t blockNum, uint8_t* buffer);

INTEGER disk_read(uint32_t lba, uint8_t* buffer, uint32_t count);
INTEGER disk_write(uint32_t lba, uint8_t* buffer, uint32_t count);

#endif /*__NOVANIX_KERNEL_HFS_HFS_H*/