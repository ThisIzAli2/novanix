/**
 * @author Ali Mirmohammad
 * @file diskcontroller.h
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
#ifndef __Novanix__SYSTEM__DISKS__DISKCONTROLLER_H
#define __Novanix__SYSTEM__DISKS__DISKCONTROLLER_H


#include <common/types.h>
#include <common/convert.h>
#include <common/memoryoperations.h>

#include <system/disks/disk.h>
#include <system/disks/diskmanager.h>

namespace Novanix
{
    namespace system
    {
        class DiskController
        {       
        public:
            DiskController();

            virtual char ReadSector(common::uint16_t drive, common::uint32_t lba, common::uint8_t* buf);
            virtual char WriteSector(common::uint16_t drive, common::uint32_t lba, common::uint8_t* buf);   
            virtual bool EjectDrive(common::uint8_t drive);         
        };
    }
}


#endif