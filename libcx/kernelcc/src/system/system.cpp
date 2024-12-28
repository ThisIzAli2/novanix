/**
 ** This file is part of Novanix.

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
#include <system/system.h>
#include <system/listings/directorylisting.h>
#include <alinix/c++/gameport.hpp>
#include <alinix/security.h>
#include <alinix/RTL8139.h>
#include <version.hpp>
#include <space.hpp>
#include <system/input/keyboardmanager.h>
#include <stringify.h>
#include <logo.h>
#include <libmath.h>
#include <delay.h>
#include <core/port.h>
#include <system/drivers/usb/usbkeyboard.h>
#include <keymap.hpp>
#include <cmdline.hpp>
#include <typing.hpp>


#define PS2_DATA_PORT 0x60
#define PS2_STATUS_PORT 0x64

__always_inline VOID readKeyboardInput() {
    uint8_t status;
    uint8_t scanCode;

    // Check if there is data to read
    status = Novanix::core::inportb(PS2_STATUS_PORT);
    if (status & 0x01 || true) { // Check if output buffer is full
        scanCode = Novanix::core::inportb(PS2_DATA_PORT);

        // Handle scan code (e.g., map to a character or process a command)
        printk(vga_color::VGA_COLOR_WHITE, "Scan Code: 0x%x\n", scanCode);
    }
}

__always_inline VOID prLogo(){

printk(vga_color::VGA_COLOR_WHITE,"                                                        \n",1);
printk(vga_color::VGA_COLOR_WHITE,",--.  ,--.                               ,--.           \n",1) ;


printk(vga_color::VGA_COLOR_WHITE,"|  ,'.|  | ,---.,--.  ,--.,--,--.,--,--, `--',--.  ,--. \n" ,1);
printk(vga_color::VGA_COLOR_WHITE,"|  |' '  || .-. |\\  `'  /' ,-.  ||      \\,--. \\  `'  /  \n",1);
printk(vga_color::VGA_COLOR_WHITE,"|  | `   |' '-' ' \\    / \\ '-'  ||  ||  ||  | /  /.  \\  \n" ,1);
printk(vga_color::VGA_COLOR_WHITE,"`--'  `--' `---'   `--'   `--`--'`--''--'`--''--'  '--'  \n",1);

}



using namespace Novanix;
using namespace Novanix::common;
using namespace Novanix::core;
using namespace Novanix::system;
using namespace Novanix::system::drivers;
using namespace Novanix;
using namespace Novanix::system::drivers;


multiboot_info_t* System::mbi = 0;
PIT* System::pit = 0;
RTC* System::rtc = 0;
DMAController* System::dma = 0;
SMBIOS* System::smbios = 0;
Virtual8086Manager* System::vm86Manager = 0;
Virtual8086Monitor* System::vm86Monitor = 0;
GraphicsDevice* System::gfxDevice = 0;
EDID* System::edid = 0;
PCIController* System::pci = 0;
DriverManager* System::driverManager = 0;
DiskManager* System::diskManager = 0;
VFSManager* System::vfs = 0;
Scheduler* System::scheduler = 0;
APMController* System::apm = 0;
SystemCallHandler* System::syscalls = 0;
SharedSystemInfo* System::systemInfo = 0;

ScreenMode System::screenMode = ScreenMode::TextMode;
BOOL System::gdbEnabled = false;
BOOL System::setupMode = false;
KeyboardManager* System::keyboardManager = 0;
Stream* System::ProcStandardOut = 0;
List<ListingController*>* System::listings = 0;
USBManager* System::usbManager = 0;
SymbolDebugger* System::kernelDebugger = 0;
#if BOCHS_GFX_HACK
bool System::isBochs = false; //are we running inside bochs
#endif
System::SYSTEM_STATS System::statistics = {};
uint16_t joyStickStat = joy_stick_status_cxx(1024);

VOID System::Start()
{
    delay(DELAY_CONSTANT);


    printk(vga_color::VGA_COLOR_WHITE,"Running the kernel keyboard",1);
    System::keyboardManager = new KeyboardManager();

    BootConsole::ForegroundColor = VGA_COLOR_BLACK;
    Log(Info, "Adding system components to kernel");
    delay(DELAY_CONSTANT);
    Log(Info, "System::Start() - Starting system initialization");
    Log(Info, "System::Start() - System initialization complete");
    System::rtc = new RTC();
    Log(Info, "- RTC [Done]     (%x)", (uint32_t)System::rtc);
    delay(DELAY_CONSTANT);

    InterruptDescriptorTable::DisableInterrupts();
    System::pit = new PIT();
    InterruptDescriptorTable::EnableInterrupts();
    delay(DELAY_CONSTANT);

    Log(Info, "- PIT [Done] [OK]    (%x)", (uint32_t)System::pit);
    delay(DELAY_CONSTANT);

    System::dma = new DMAController();
    Log(Info, "- DMA [Done] [OK]     (%x)", (uint32_t)System::dma);
    delay(DELAY_CONSTANT);

    System::smbios = new SMBIOS();
    Log(Info, "- SMBIOS [Done]     (%x)", (uint32_t)System::smbios);
    printk(vga_color::VGA_COLOR_GREEN,"   ,  Running novanix kernel %s",1,KERNEL_VERSION);
    delay(DELAY_CONSTANT);

    Log(Info, "Adding Virtual 8086");
    System::vm86Manager = new Virtual8086Manager();
    System::vm86Monitor = new Virtual8086Monitor();
    delay(DELAY_CONSTANT);

    // The graphics component is added here but not used right away, we don't need to be in video mode so early.
    System::gfxDevice = GraphicsDevice::GetBestDevice();
    Log(Info, "- GFX [Done]     (%x)", (uint32_t)System::gfxDevice);
    Serialport::WriteStr("HIIII");
    delay(DELAY_CONSTANT);

    // Check for monitor EDID
    System::edid = new EDID();
    Log(Info, "- EDID [Done]     (%x)", (uint32_t)System::edid);
    System::edid->AcquireEDID();
    delay(DELAY_CONSTANT);

    // Start the rtl 
    Log(Info,"[OK] calling the RTL constructor");
    // printk(vga_color::VGA_COLOR_BLUE,"Hello world,1");
    init_rtl();
    delay(DELAY_CONSTANT);

    Log(Info, "Loading Initial Ramdisk [OK]");
    InitialRamDisk::Initialize(System::mbi);
    Log(Info, "Loading Initial Novanix Kernel Base...\n");

    delay(DELAY_CONSTANT);

    System::pci = new PCIController();
    Log(Info, "- PCI [Done]     (%x)", (uint32_t)System::pci);
    Log(Info,"JoyStick driver status: %d",joyStickStat);
    
    System::pci->PopulateDeviceList();

    delay(DELAY_CONSTANT);

    Log(Info, "Starting Driver Manager");
    System::driverManager = new DriverManager();

    Log(Info, "Starting Disk Manager");
    System::diskManager = new DiskManager();
    delay(DELAY_CONSTANT);

    Log(Warning, "Starting Keyboard Manager");
    System::keyboardManager = new KeyboardManager();

    Log(Info, "\n[OK]");
    delay(DELAY_CONSTANT);


    Log(Info, "Starting Scheduler");
    InterruptDescriptorTable::DisableInterrupts();
    System::scheduler = new Scheduler();
    InterruptDescriptorTable::EnableInterrupts();

    Log(Info, "Starting USB Manager");
    System::usbManager = new USBManager();
    Log(Info, "Initializing Virtual File System");
    System::vfs = new VFSManager();

    Log(Info, "Setting up random...");
    Random::SetSeed(pit->Ticks());
    delay(DELAY_CONSTANT);


    Log(Info, "Assigning PCI Drivers");
    PCIDrivers::AssignDriversFromPCI(System::pci, System::driverManager);

    Log(Info, "Creating shared region for system info");
    System::systemInfo = (SharedSystemInfo*)KernelHeap::alignedMalloc(PAGE_SIZE, PAGE_SIZE);
    MemoryOperations::memset(System::systemInfo, 0, PAGE_SIZE);
    delay(DELAY_CONSTANT);

    Log(Info, "Added drivers for integrated devices");
    System::driverManager->AddDriver(new PS2MouseDriver());
    System::driverManager->AddDriver(new PS2KeyboardDriver());
    System::driverManager->AddDriver(new FloppyDriver());
    
    Log(Info, "Activating Drivers");
    System::driverManager->ActivateAll();
    delay(DELAY_CONSTANT);

    Log(Info, "Setting up found USB controllers");
    System::usbManager->SetupAll();
    Log(Info, "Setting up found USB devices");
    System::usbManager->AssignAllDrivers();
    System::usbManager->USBPoll();
    delay(DELAY_CONSTANT);

    // Advanced Power Management
    System::apm = new APMController();

    Log(Info, "Found a total of: %d disks", System::diskManager->allDisks.size());
    BootConsole::Write("Searching for boot partition");
    if(System::vfs->SearchBootPartition()) {
        BootConsole::Write(" [Found] ("); BootConsole::Write(Convert::IntToString(System::vfs->bootPartitionID)); BootConsole::WriteLine(")");
    }
    else
        BootConsole::WriteLine(" [Not found]");

    Log(Info, "Starting Debugger");
    System::kernelDebugger = new SymbolDebugger("B:\\debug.sym", true);
    delay(DELAY_CONSTANT);

    Log(Info, "Starting Systemcalls");
    System::syscalls = new SystemCallHandler();
    delay(DELAY_CONSTANT);

    Log(Info, "Preparing IPC");
    IPCManager::Initialize();
    delay(DELAY_CONSTANT);

    Log(Info, "Adding default listing handlers");
    System::listings = new List<ListingController*>();
    System::listings->push_back(new DirectoryListing());
    delay(DELAY_CONSTANT);

    System::ProcStandardOut = new StandardOutSteam();
    Log(Info, "System Initialized");
}
void System::Panic()
{
    Log(Error, "-------------------------------");
    Log(Error, "--------- Kernel Halted -------");
    Log(Error, "-------------------------------");
    InterruptDescriptorTable::DisableInterrupts();
    for (;;) {
        printk(vga_color::VGA_COLOR_WHITE,"Stopping the kernel",1);
        // printk(vga_color::VGA_COLOR_WHITE,stringify(1/0.0000001));
        printk(vga_color::VGA_COLOR_WHITE,LOGO_KERNEL,1);
        prLogo();
        printk(vga_color::VGA_COLOR_WHITE,"\n\n\n\n\n\n\n\n\n\n",1);
        printk(vga_color::VGA_COLOR_WHITE,"Kernel Booted ",1);
        printk(vga_color::VGA_COLOR_WHITE,"--------------------------------------------------",1);
        printk(vga_color::VGA_COLOR_GREEN,"Starting the keyboard",1);
        // readKeyboardInput();
        printk(VGA_COLOR_WHITE,"Press any key to continue...",1);
        Log(Error,"Failed to boot kernel GUI, switching to CUI...");
        cmdline();
        // setup_interrupts_and_keyboard();
        printk(vga_color::VGA_COLOR_GREEN,"Started the keyboard",1);
        // printk(VGA_COLOR_WHITE, "%s","Welcome to Novanix!");
        asm("hlt");
        asm("nop");
    }
}