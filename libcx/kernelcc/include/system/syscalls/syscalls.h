#ifndef __Novanix__SYSTEM__SYSCALLS__SYSCALLS_H
#define __Novanix__SYSTEM__SYSCALLS__SYSCALLS_H

#include <system/interruptmanager.h>

namespace Novanix
{
    namespace system
    {
        class SystemCallHandler : public InterruptHandler
        {
        public:
            SystemCallHandler();

            common::uint32_t HandleInterrupt(common::uint32_t esp);
        };
    }
}

#endif