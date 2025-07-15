/**
 * @author Ali Mirmohammad
 * @file disk.cpp
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
#include <system/disks/disk.h>
#include <system/system.h>

using namespace Novanix;
using namespace Novanix::common;
using namespace Novanix::system;

Disk::Disk(uint32_t controllerIndex, DiskController* controller, DiskType type, uint64_t size, uint32_t blocks, uint32_t blocksize)
{
    this->controllerIndex = controllerIndex;
    this->controller = controller;
    this->type = type;
    this->size = size;
    this->blockSize = blocksize;
    this->numBlocks = blocks;
}
char Disk::ReadSector(uint32_t lba, uint8_t* buf)
{
    #if ENABLE_ADV_DEBUG
    System::statistics.diskReadOp += 1;
    #endif

    if(this->controller != 0)
        return this->controller->ReadSector(this->controllerIndex, lba, buf);
    return 1;
}
char Disk::WriteSector(uint32_t lba, uint8_t* buf)
{
    #if ENABLE_ADV_DEBUG
    System::statistics.diskWriteOp += 1;
    #endif

    if(this->controller != 0)
        return this->controller->WriteSector(this->controllerIndex, lba, buf);
    return 1;
}