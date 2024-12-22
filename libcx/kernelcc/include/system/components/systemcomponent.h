#ifndef __Novanix__SYSTEM__COMPONENTS_H
#define __Novanix__SYSTEM__COMPONENTS_H

#include <common/types.h>

namespace Novanix
{
    namespace system
    {
        class SystemComponent
        {
        private:
            char* Name;
            char* Description;
        public:
            SystemComponent(char* name = 0, char* description = 0);

            char* GetComponentName();
            char* GetComponentDescription();
        };
    }
}

#endif