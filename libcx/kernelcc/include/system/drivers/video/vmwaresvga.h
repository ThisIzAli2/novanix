/**
 * @author Ali Mirmohammad
 * @file vmwaresvga.h
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
#ifndef __Novanix__SYSTEM__DRIVERS__VMWARESVGA_H
#define __Novanix__SYSTEM__DRIVERS__VMWARESVGA_H

#include <system/drivers/driver.h>
#include <system/components/pci.h>
#include <system/interruptmanager.h>
#include <system/components/graphicsdevice.h>

namespace Novanix
{
    namespace system
    {
        namespace drivers
        {
            #define VMWARESVGAII_VENDORID 0x15AD
            #define VMWARESVGAII_DEVICEID 0x0405

            #define SVGA_INDEX_PORT         0x0
            #define SVGA_VALUE_PORT         0x1
            #define SVGA_BIOS_PORT          0x2
            #define SVGA_IRQSTATUS_PORT     0x8

            #define SVGA_MAGIC         0x900000UL
            #define SVGA_MAKE_ID(ver)  (SVGA_MAGIC << 8 | (ver))

            /* Version 2 let the address of the frame buffer be unsigned on Win32 */
            #define SVGA_VERSION_2     2
            #define SVGA_ID_2          SVGA_MAKE_ID(SVGA_VERSION_2)

            #define SVGA_REG_ID 0
            #define SVGA_REG_FB_START 13
            #define SVGA_REG_FB_Enable 1
            #define SVGA_REG_FB_Width 2
            #define SVGA_REG_FB_Height 3
            #define SVGA_REG_FB_BitsPerPixel 7

            class VMWARESVGAII : public Driver, public GraphicsDevice
            {
            private:
                PCIDevice* pciDevice;

                void WriteRegister(common::uint32_t reg, common::uint32_t value);
                common::uint32_t ReadRegister(common::uint32_t reg);
            public:
                VMWARESVGAII(PCIDevice* pciDev);

                bool Initialize();
                bool SelectBestVideoMode();
            };
        }
    }
}

#endif