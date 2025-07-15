/**
 * @author Ali Mirmohammad
 * @file syscalls.cpp
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
#include <system/syscalls/syscalls.h>

#include <system/system.h>
#include <system/syscalls/implementations/Novanix.h>
#include <system/syscalls/implementations/linux.h>

using namespace Novanix;
using namespace Novanix::common;
using namespace Novanix::system;
using namespace Novanix::core;

SystemCallHandler::SystemCallHandler()
: InterruptHandler(0x80) {

}

uint32_t SystemCallHandler::HandleInterrupt(uint32_t esp)
{
    //Interrupts need to be enabled for io system calls
    InterruptDescriptorTable::EnableInterrupts();

    int ID = System::scheduler->CurrentProcess()->syscallID;

    switch (ID)
    {
        case 0: //Linux Systemcall
            return (uint32_t)LinuxSyscalls::HandleSyscall((CPUState*)esp);
            break;
        case 1: //Novanix Systemcall
            return (uint32_t)NovanixSyscalls::HandleSyscall((CPUState*)esp);
            break;   
        default:
            Log(Error, "Process %d has unkown syscallID %d", System::scheduler->CurrentProcess()->syscallID, ID);
            break;
    }

    //Restore previous state
    InterruptDescriptorTable::DisableInterrupts();

    return esp;
}