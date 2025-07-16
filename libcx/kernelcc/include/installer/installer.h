/**
 * @author Ali Mirmohammad
 * @file installer.h
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
#ifndef __Novanix__INSTALLER__INSTALLER_H
#define __Novanix__INSTALLER__INSTALLER_H

#include <system/disks/partitionmanager.h>
#include <system/vfs/fat.h>

namespace Novanix
{
    // Class responsible for installing Novanix on a hard drive
    class Installer
    {
    public:
        static void SetupError();
        static void Run();
        static char GetKey();

        // Installer Steps
        static void ShowWelcomeMessage();
        static void ShowWarningMessage();
        static void ShowDiskSelection();
        static void ShowDiskEraseMenu();
        static void ShowInstallScreen();
        static void ShowSystemCopyScreen(system::FAT* fatFS);
        static void CreateFatPartition(system::PartitionTableEntry* pEntry);
    };

    #define KEY_ENTER       0x1C
    #define KEY_ARROW_UP    0x48
    #define KEY_ARROW_DOWN  0x50
    #define KEY_LEFT_ARROW  0x33
    #define KEY_RIGHT_ARROW 0x34
    #define KEY_MINUS       0x0C
    #define KEY_PLUS        0x0D
    #define KEY_A           0x1E
}

#endif