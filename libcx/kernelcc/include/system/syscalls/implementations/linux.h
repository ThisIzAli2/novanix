#ifndef __Novanix__SYSTEM__SYSCALLS__IMPLEMENTATIONS_LINUX_H
#define __Novanix__SYSTEM__SYSCALLS__IMPLEMENTATIONS_LINUX_H

#include <core/registers.h>

namespace Novanix
{
    namespace system
    {
        class LinuxSyscalls
        {
        public:
            static core::CPUState* HandleSyscall(core::CPUState* state);
        };
    }
}

#endif