#include <system/syscalls/implementations/linux.h>

#include <system/system.h>

using namespace Novanix;
using namespace Novanix::common;
using namespace Novanix::core;
using namespace Novanix::system;

CPUState* LinuxSyscalls::HandleSyscall(CPUState* state)
{
    switch (state->EAX)
    {
        case 0xFFFF: //We use this systemcall for setting the Novanix Syscall implementation for this process since linux is the default one
            //From now on this uses Novanix Systemcalls
            System::scheduler->CurrentProcess()->syscallID = 1;
            //Return a succes
            state->EAX = System::scheduler->CurrentProcess()->id; //Return the pid
            break;
    
        default:
            state->EAX = 0;
            break;
    }

    return state;
}