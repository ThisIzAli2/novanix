/**
 * @author Ali Mirmohammad
 * @file vfsmanager.h
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

#ifndef __ALINIX_KERNEL_VFS_VFSMANAGER_H
#define __ALINIX_KERNEL_VFS_VFSMANAGER_H

#include <alinix/disk/disk.h>
#include <alinix/vfs/virtualfilesystem.h>
#include <alinix/fs/fat.h>

int bootPartitionID = -1;
void Mount(VirtualFileSystem* vfs);
void Unmount(VirtualFileSystem* vfs);
void UnmountByDisk(Disk* disk);

#endif /*__ALINIX_KERNEL_VFS_VFSMANAGER_H*/