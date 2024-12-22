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