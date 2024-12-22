/**
 * @author Ali Mirmohammad
 * @file system.hpp
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
 *  - Kernel header file for system settings for C++.
*/
#ifndef __ALINIX_KERNEL_SYSTEM_HPP
#define __ALINIX_KERNEL_SYSTEM_HPP


#ifndef __cplusplus
# error "This file must be compiled with C++"

#endif /*__cplusplus*/

#include <alinix/systeminfo.h>
#include <alinix/print.h>
#include <alinix/printk.h>
#include <alinix/stream.hpp>
#include <alinix/enums.h>
#include <alinix/system.h>
#include <alinix/components/graphicdevice.hpp>

#define DEFAULT_SCREEN_WIDTH 1024
#define DEFAULT_SCREEN_HEIGHT 768
#define DEFAULT_SCREEN_BPP 32

// enum ScreenMode
// {
//     TextMode,
//     GraphicsMode
// };

// enum PowerRequest
// {
//     None,
//     Shutdown,
//     Reboot
// };

/**
 * The default stream where processes data is send to.
 * Data is send to the screen/serial output
*/
class StandardOutSteam : public Stream
{
public:
    // StandardOutSteam() : Stream() {}

    // We only overwrite the write function since reading is not supported
    void Write(char byte)
    {
        char str[1];
        str[0] = byte;
        Print(str, 1);
    }
};     

class System
{
public:
    // static multiboot_info_t* mbi;
    // static PIT* pit;
    // static RTC* rtc;
    // static SMBIOS* smbios;
    // static DMAController* dma;
    // static Virtual8086Manager* vm86Manager;
    // static Virtual8086Monitor* vm86Monitor;
    static GraphicsDevice* gfxDevice;
    // static EDID* edid;
    // static PCIController* pci;
    // static drivers::DriverManager* driverManager;
    // static DiskManager* diskManager;
    // static VFSManager* vfs;
    // static Scheduler* scheduler;
    // static SystemCallHandler* syscalls;
    // static APMController* apm;
    static SharedSystemInfo* systemInfo;

    // static ScreenMode screenMode;
    static bool gdbEnabled; //Is the gdb stub enabled?
    static bool setupMode; //Are we running the setup program?
    // static KeyboardManager* keyboardManager;
    // static Stream* ProcStandardOut;
    // static List<ListingController*>* listings;
    // static USBManager* usbManager;
    // static SymbolDebugger* kernelDebugger;
    // #if BOCHS_GFX_HACK
    static bool isBochs; //are we running inside bochs
    // #endif

    #if ENABLE_ADV_DEBUG
    typedef struct
    {
        // Values for measuring activity of idle process
        uint32_t idleProcCounter = 0;
        uint32_t idleProcStartTime = 0;
        uint32_t idleProcActive = 0;

        // Amount of disk read operations
        uint32_t diskReadOp = 0;

        // Amount of disk write operations
        uint32_t diskWriteOp = 0;
    } SYSTEM_STATS;
    static SYSTEM_STATS statistics;
    #endif /*ENABLE_ADV_DEBUG*/

    static void Start();
    static void Panic();
};

#endif /*__ALINIX_KERNEL_SYSTEM_HPP*/