/**
 * @author Ali Mirmohammad
 * @file disk.h
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
#ifndef __Novanix__SYSTEM__DISKS__DISK_H
#define __Novanix__SYSTEM__DISKS__DISK_H

#include <common/types.h>

#include <system/disks/diskcontroller.h>

namespace Novanix
{
    namespace system
    {
        class DiskController;

        enum DiskType
        {
            HardDisk,
            USBDisk,
            Floppy,
            CDROM
        };

        class Disk
        {
        public:
            DiskController* controller;         // Which controller is controling this disk device
            common::uint32_t controllerIndex;   // The real number for the disk on the controller
            char* identifier = 0;               // Disk Identifier
            DiskType type;              // Type of disk
            common::uint64_t size;      // Size of disk in bytes
            common::uint32_t numBlocks; // Number of data blocks
            common::uint32_t blockSize; // Size of one block of data

            Disk(common::uint32_t controllerIndex, DiskController* controller, DiskType type, common::uint64_t size, common::uint32_t blocks, common::uint32_t blocksize);
            
            virtual char ReadSector(common::uint32_t lba, common::uint8_t* buf);          
            virtual char WriteSector(common::uint32_t lba, common::uint8_t* buf);
        };
    }
}

#endif