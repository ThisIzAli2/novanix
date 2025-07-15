/**
 * @author Ali Mirmohammad
 * @file virtualfilesystem.cpp
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
#include <system/vfs/virtualfilesystem.h>
#include <system/log.h>
#include <typing.hpp>

using namespace Novanix::common;
using namespace Novanix::core;
using namespace Novanix::system;

VirtualFileSystem::VirtualFileSystem(Disk* disk, common::uint32_t start, common::uint32_t size, char* name)
{
    this->disk = disk;
    this->SizeInSectors = size;
    this->StartLBA = start;
    this->Name = name;
}

VirtualFileSystem::~VirtualFileSystem()
{
    Log(Error, "Virtual function called directly %s:%d", __FILE__, __LINE__);
}

BOOL VirtualFileSystem::Initialize()
{
    return false;
}

INTEGER VirtualFileSystem::ReadFile(const char* filename, uint8_t* buffer, uint32_t offset, uint32_t len)
{
    Log(Error, "Virtual function called directly %s:%d", __FILE__, __LINE__);
    return -1;
}
INTEGER VirtualFileSystem::WriteFile(const char* filename, uint8_t* buffer, uint32_t len, BOOL create)
{
    Log(Error, "Virtual function called directly %s:%d", __FILE__, __LINE__);
    return -1;
}
BOOL VirtualFileSystem::FileExists(const char* filename)
{
    Log(Error, "Virtual function called directly %s:%d", __FILE__, __LINE__);
    return false;
}
BOOL VirtualFileSystem::DirectoryExists(const char* filename)
{
    Log(Error, "Virtual function called directly %s:%d", __FILE__, __LINE__);
    return false;
}
INTEGER VirtualFileSystem::CreateFile(const char* path)
{
    Log(Error, "Virtual function called directly %s:%d", __FILE__, __LINE__);
    return -1;
}
INTEGER VirtualFileSystem::CreateDirectory(const char* path)
{
    Log(Error, "Virtual function called directly %s:%d", __FILE__, __LINE__);
    return -1;
}
uint32_t VirtualFileSystem::GetFileSize(const char* filename)
{
    Log(Error, "Virtual function called directly %s:%d", __FILE__, __LINE__);
    return -1;
}
List<Novanix::VFSEntry>* VirtualFileSystem::DirectoryList(const char* path)
{
    Log(Error, "Virtual function called directly %s:%d", __FILE__, __LINE__);
    return 0;
}