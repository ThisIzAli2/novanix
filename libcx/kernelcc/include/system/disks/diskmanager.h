/**
 * @author Ali Mirmohammad
 * @file diskmanager.h
 * @Credits Remco123
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
#ifndef __Novanix__SYSTEM__DISKS__DISKMANAGER_H
#define __Novanix__SYSTEM__DISKS__DISKMANAGER_H


#include <common/types.h>
#include <common/convert.h>
#include <common/string.h>
#include <common/memoryoperations.h>
#include <common/list.h>

#include <system/bootconsole.h>
#include <system/disks/disk.h>

namespace Novanix
{
    namespace system
    {
        struct BiosDriveParameters
        {
            common::uint16_t bufLen;
            common::uint16_t infoFlags;
            common::uint32_t cilinders;
            common::uint32_t heads;
            common::uint32_t sectorsPerTrack;
            common::uint64_t totalSectors;
            common::uint16_t bytesPerSector;

            common::uint32_t eddParameters;

            common::uint16_t signature;
            common::uint8_t  devPathLen;
            common::uint8_t  reserved1[3];
            char             hostBusName[4];
            char             interfaceName[8];
            common::uint8_t  interfacePath[8];
            common::uint8_t  devicePath[8];
            common::uint8_t  reserved2;
            common::uint8_t  checksum;
        } __attribute__((packed));

        class Disk;
        class DiskManager
        {
        public:
            List<Disk*> allDisks;

            DiskManager();

            //Add disk to system and check for filesystems
            void AddDisk(Disk* disk);
            //Remove disk from system and unmount filesystems
            void RemoveDisk(Disk* disk);

            char ReadSector(common::uint16_t drive, common::uint32_t lba, common::uint8_t* buf);
            char WriteSector(common::uint16_t drive, common::uint32_t lba, common::uint8_t* buf);

            BiosDriveParameters* GetDriveInfoBios(common::uint8_t drive);
        };
    }
}


#endif