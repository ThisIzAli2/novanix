/**
 * @author Ali Mirmohammad
 * @file vfs.cpp
 * Credits Remco123
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

#include <vfs.h>

#include <syscall.h>
#include <listing.h>

using namespace Novanix;

bool Novanix::FileExists(char* path)
{
    return (bool)DoSyscall(SYSCALL_FILE_EXISTS, (uint32_t)path);
}
uint32_t Novanix::GetFileSize(char* path)
{
    return (uint32_t)DoSyscall(SYSCALL_GET_FILESIZE, (uint32_t)path);
}
int Novanix::ReadFile(char* path, uint8_t* buffer, uint32_t offset, uint32_t len)
{
    return (int)DoSyscall(SYSCALL_READ_FILE, (uint32_t)path, (uint32_t)buffer, offset, len);
}
int Novanix::WriteFile(char* path, uint8_t* buffer, uint32_t len, bool create)
{
    return (int)DoSyscall(SYSCALL_WRITE_FILE, (uint32_t)path, (uint32_t)buffer, len, (uint32_t)create);
}
int Novanix::CreateFile(char* path)
{
    return (int)DoSyscall(SYSCALL_CREATE_FILE, (uint32_t)path);
}
int Novanix::CreateDirectory(char* path)
{
    return (int)DoSyscall(SYSCALL_CREATE_DIRECTORY, (uint32_t)path);
}
bool Novanix::DirectoryExists(char* path)
{
    return (bool)DoSyscall(SYSCALL_DIR_EXISTS, (uint32_t)path);
}
bool Novanix::EjectDisk(char* path)
{
    return (bool)DoSyscall(SYSCALL_EJECT_DISK, (uint32_t)path);
}
List<VFSEntry> Novanix::DirectoryListing(char* path)
{
    List<VFSEntry> result;

    int items = DoSyscall(SYSCALL_BEGIN_LISTING, DIRECTORY_LISTING, (uint32_t)path);
    if(items == -1)
        return result;
    
    for(int i = 0; i < items; i++) {
        VFSEntry entry;
        int strLen = DoSyscall(SYSCALL_LISTING_ENTRY, DIRECTORY_LISTING, (uint32_t)i, (uint32_t)&entry);
        if(strLen == 0)
            return result; // End of items

        result += entry;
    }
    DoSyscall(SYSCALL_END_LISTING, DIRECTORY_LISTING);
    return result;
}