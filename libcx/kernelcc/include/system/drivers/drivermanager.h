#ifndef __Novanix__SYSTEM__DRIVERMANAGER__DRIVER_H
#define __Novanix__SYSTEM__DRIVERMANAGER__DRIVER_H

#include <common/types.h>
#include <common/list.h>

#include <system/drivers/driver.h>
#include <system/bootconsole.h>

namespace Novanix
{
    namespace system
    {
        namespace drivers
        {
            class DriverManager
            {
            private:
                List<Driver*> driverList;
            public:
                DriverManager();

                void AddDriver(Driver* drv);

                void ActivateAll();
            };
        }
    }
}

#endif