/**
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
 * MIT License

Copyright (c) 2020 Remco123

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/
#include <system/initrd.h>
#include <system/log.h>

using namespace CactusOS;
using namespace CactusOS::common;
using namespace CactusOS::system;

void* locationInMemory = 0;

void InitialRamDisk::Initialize(multiboot_info_t* mbi)
{
    if(mbi->mods_count <= 0)
    {
        Log(Info, "Error mods count is 0 or less");
        return;
    }
    
    uint32_t ramdiskLocation = *(uint32_t*)mbi->mods_addr;
    uint32_t ramdiskEnd = *(uint32_t*)(mbi->mods_addr + 4);

    Log(Info, "Ramdisk is at: %x", ramdiskLocation);
    Log(Info, "Ramdisk size: %d", ramdiskEnd - ramdiskLocation);

    locationInMemory = (void*)ramdiskLocation;
}

void* InitialRamDisk::ReadFile(const char* path, uint32_t* fileSizeReturn)
{
    InitrdFileHeader* header = (InitrdFileHeader*)locationInMemory;
    while(header->size != 0)
    {
        if(String::strcmp(header->path, path))
        {
            if(fileSizeReturn != 0)
                *fileSizeReturn = header->size;
            return (void*)((uint32_t)header + sizeof(InitrdFileHeader));
        }
        
        header = (InitrdFileHeader*)((uint32_t)header + sizeof(InitrdFileHeader) + header->size);
    }
    return 0;
}