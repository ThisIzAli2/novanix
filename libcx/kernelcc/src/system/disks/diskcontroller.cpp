/**
 * @author Ali Mirmohammad
 * @file diskcontroller.cpp
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
#include <system/disks/diskcontroller.h>

using namespace Novanix;
using namespace Novanix::common;
using namespace Novanix::system;

DiskController::DiskController()
{ }
char DiskController::ReadSector(uint16_t drive, uint32_t lba, uint8_t* buf)
{ return 1; } //Needs to be implemented by driver
char DiskController::WriteSector(uint16_t drive, uint32_t lba, uint8_t* buf)
{ return 1; } //Needs to be implemented by driver
bool DiskController::EjectDrive(uint8_t drive)
{ return false; } //Needs to be implemented by driver