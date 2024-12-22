#ifndef __Novanix__SYSTEM__SYSCALLS__IMPLEMENTATIONS_Novanix_H
#define __Novanix__SYSTEM__SYSCALLS__IMPLEMENTATIONS_Novanix_H

#include <core/registers.h>

namespace Novanix
{
    namespace system
    {
        class NovanixSyscalls
        {
        public:
            static core::CPUState* HandleSyscall(core::CPUState* state);
        };
    }
}

#endif