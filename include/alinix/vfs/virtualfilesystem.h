/**
 * @author Ali Mirmohammad
 * @file virtualfilesystem.h
 * *************************************IMPORTANT ALINIX LICENSE TERM********************************************
 ** This file is part of AliNix.

**AliNix is free software: you can redistribute it and/or modify
**it under the terms of the GNU Affero General Public License as published by
**the Free Software Foundation, either version 3 of the License, or
**(at your option) any later version.

**AliNix is distributed in the hope that it will be useful,
**but WITHOUT ANY WARRANTY; without even the implied warranty of
**MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
**GNU Affero General Public License for more details.

**You should have received a copy of the GNU Affero General Public License
**along with AliNix. If not, see <https://www.gnu.org/licenses/>.
*/

/**
 * @abstraction:
 *  - Kernel virtual file system header file driver util.
*/

#ifndef __ALINIX_KERNEL_VIRTUAL_FILE_SYSTEM_VFS_H
#define __ALINIX_KERNEL_VIRTUAL_FILE_SYSTEM_VFS_H


#include <alinix/types.h>
#include <alinix/memory.h>
#include <alinix/ulib.h>

#define PATH_SEPERATOR_C '\\' //Path Seperator as char
#define PATH_SEPERATOR_S "\\" //Path Seperator as string


typedef struct VirtualFileSystem {
    Disk* disk;
    uint32_t StartLBA;
    uint32_t SizeInSectors;
    char* Name;
} VirtualFileSystem;

VirtualFileSystem* VirtualFileSystem_create(Disk* disk, uint32_t start, uint32_t size, char* name);
            
bool Initialize();

/////////////
// VFS Functions (Read, Write, etc.)
///////////// 
    
// Read file contents into buffer
int ReadFile(const char* filename, uint8_t* buffer, uint32_t offset, uint32_t len);
// Write buffer to file, file will be created when create equals true
int WriteFile(const char* filename, uint8_t* buffer, uint32_t len, bool create);

// Check if file exist
bool FileExists(const char* filename);
// Check if directory exist
bool DirectoryExists(const char* filename);

// Create a file at the filepath
int CreateFile(const char* path);
// Create a new directory
int CreateDirectory(const char* path);

// Get size of specified file in bytes
uint32_t GetFileSize(const char* filename);

#endif /*__ALINIX_KERNEL_VIRTUAL_FILE_SYSTEM_VFS_H*/