/**
 * @author Ali Mirmohammad
 * @file hfs.cpp
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
#include <fs/hfs/hfs.h>
#include <fs/diskio.h>
#include <fs/hfs/fstruct.h>
#include <system/log.h>
#include <stringify.h>

using namespace Novanix::system;

extern hfs_volume_header_t volume;

VOID hfs_read_block(uint32_t blockNum, uint8_t* buffer) {
    disk_read(blockNum,buffer,512);
}

VOID hfs_write_block(uint32_t blockNum, uint8_t* buffer){
    disk_write(blockNum, buffer, 512);
}

VOID hfs_mount(){
    hfs_read_block(2,(uint8_t*)&volume);

    if (volume.signature[0] != 'H' || volume.signature[1] != '+'){
        printk(VGA_COLOR_WHITE,"Not ready for HFS",1);
        return;
    }
    printk(VGA_COLOR_WHITE,"HFS mounted on",1);
    printk(VGA_COLOR_WHITE,stringify(volume.blockSize),1);


}