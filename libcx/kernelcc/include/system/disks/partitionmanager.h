/**
 * @author Ali Mirmohammad
 * @file partionmanager.h
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
#ifndef __Novanix__SYSTEM__DISKS__PARTITIONMANAGER_H
#define __Novanix__SYSTEM__DISKS__PARTITIONMANAGER_H

#include <system/disks/diskmanager.h>
#include <system/vfs/vfsmanager.h>

namespace Novanix
{
    namespace system
    {
        struct PartitionTableEntry
        {
            common::uint8_t bootable;

            common::uint8_t start_head;
            common::uint8_t start_sector : 6;
            common::uint16_t start_cylinder : 10;

            common::uint8_t partition_id;

            common::uint8_t end_head;
            common::uint8_t end_sector : 6;
            common::uint16_t end_cylinder : 10;
            
            common::uint32_t start_lba;
            common::uint32_t length;
        } __attribute__((packed));
        

        struct MasterBootRecord
        {
            common::uint8_t bootloader[440];
            common::uint32_t signature;
            common::uint16_t unused;
            
            PartitionTableEntry primaryPartitions[4];
            
            common::uint16_t magicnumber;
        } __attribute__((packed));

        class PartitionManager
        {
        private:
            //Check partition type and assign filesystem driver if available
            static void AssignVFS(PartitionTableEntry partition, Disk* disk);
        public:
            //Read partition descriptor of disk and assign fileysysem if possible
            static void DetectAndLoadFilesystem(Disk* disk);
        };
    }
}

#endif