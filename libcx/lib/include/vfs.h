/**
 * @author Ali Mirmohammad
 * @file vfs.h
 * @credits remco123
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
#ifndef __NovanixLIB__VFS_H
#define __NovanixLIB__VFS_H

#include <types.h>
#include <list.h>
#include <shared.h>

namespace Novanix
{
    // Read file contents into buffer
    int ReadFile(char* filename, uint8_t* buffer, uint32_t offset = 0, uint32_t len = -1);
    // Write buffer to file, file will be created when create equals true
    int WriteFile(char* filename, uint8_t* buffer, uint32_t len, bool create = true);

    // Check if file exist
    bool FileExists(char* filename);
    // Check if directory exist
    bool DirectoryExists(char* filename);

    // Create a file at the filepath
    int CreateFile(char* path);
    // Create a new directory
    int CreateDirectory(char* path);

    // Get size of specified file in bytes
    uint32_t GetFileSize(char* filename);

    // Get list of files/directories in specified path
    List<VFSEntry> DirectoryListing(char* path);

    // Request to eject a specific disk (only works for CD's at the moment, TODO: usb as well?)
    bool EjectDisk(char* path);
}

#endif