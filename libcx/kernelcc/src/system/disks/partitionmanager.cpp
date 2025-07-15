/**
 * @author Ali Mirmohammad
 * @file partionmanager.cpp
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
#include <system/disks/partitionmanager.h>

#include <system/vfs/iso9660.h>
#include <system/vfs/fat.h>
#include <system/system.h>

using namespace Novanix;
using namespace Novanix::common;
using namespace Novanix::core;
using namespace Novanix::system;

void PartitionManager::DetectAndLoadFilesystem(Disk* disk)
{
    char* diskIdentifier = (char*)(disk->identifier == 0 ? "" : disk->identifier);
    Log(Info, "Detecting partitions on disk %s", diskIdentifier);
    
    uint8_t* Readbuf = new uint8_t[CDROM_SECTOR_SIZE];
    MemoryOperations::memset(Readbuf, 0, CDROM_SECTOR_SIZE);

    char ret = disk->ReadSector(0, Readbuf);
    if(ret == 0)
    {
        MasterBootRecord* mbr = (MasterBootRecord*)Readbuf;
        if(mbr->magicnumber != 0xAA55) {
            Log(Warning, "MBR magic number is not 0xAA55 instead %w", mbr->magicnumber);
            delete Readbuf;
            return;
        }

        if(disk->type == DiskType::Floppy) // Floppy don't contain partitions
        {
            FAT* fatFS = new FAT(disk, 0, disk->size / BYTES_PER_SECT);
            if(fatFS->Initialize())
                System::vfs->Mount(fatFS); //Mount the filesystem
            else
                delete fatFS;
        }
        else // Regular partition scheme 
        {
            //Loop trough partitions
            for(int p = 0; p < 4; p++)
            {
                if(mbr->primaryPartitions[p].partition_id == 0x00)
                    continue;

                Log(Info, "- Disk %s Part=%d Boot=%d ID=%b Sectors=%d", diskIdentifier, p, mbr->primaryPartitions[p].bootable == 0x80, mbr->primaryPartitions[p].partition_id, mbr->primaryPartitions[p].length);
                AssignVFS(mbr->primaryPartitions[p], disk);
            }
        }
    }
    else {
        Log(Error, "Error reading disk %s code = %b", diskIdentifier, ret);
    }
    delete Readbuf;
}

void PartitionManager::AssignVFS(PartitionTableEntry partition, Disk* disk)
{
    if(partition.partition_id == 0xCD)
    {
        BootConsole::Write(" [ISO9660]");
        ISO9660* isoVFS = new ISO9660(disk, partition.start_lba, partition.length);
        if(isoVFS->Initialize())
            System::vfs->Mount(isoVFS); //Mount the filesystem
        else
            delete isoVFS;
    }
    else if(partition.partition_id == 0x0B || partition.partition_id == 0x0C || partition.partition_id == 0x01 || partition.partition_id == 0x04 || partition.partition_id == 0x06)
    {
        BootConsole::WriteLine(" [FAT(12/16/32)]");
        FAT* fatFS = new FAT(disk, partition.start_lba, partition.length);
        if(fatFS->Initialize())
            System::vfs->Mount(fatFS); //Mount the filesystem
        else
            delete fatFS;
    }
}