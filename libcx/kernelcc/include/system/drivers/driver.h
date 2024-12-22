#ifndef __Novanix__SYSTEM__DRIVER_H
#define __Novanix__SYSTEM__DRIVER_H

namespace Novanix
{
    namespace system
    {
        namespace drivers
        {
            class Driver
            {
            private:
                char* Name;
                char* Description;
            public:
                Driver(char* name = 0, char* description = 0);

                char* GetDriverName();
                char* GetDriverDescription();

                virtual bool Initialize();
            };
        }
    }
}

#endif