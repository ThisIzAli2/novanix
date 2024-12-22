#ifndef __Novanix__CORE__POWER_H
#define __Novanix__CORE__POWER_H

#include <core/port.h>

namespace Novanix
{
    namespace core
    {
        class Power
        {
        public:
            static void Initialize();
            static void Reboot();
            static void Poweroff();
        };
    }
}

#endif