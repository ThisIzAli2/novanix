/**
 * @author Ali Mirmohammad
 * @file apm.cpp
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
/*
https://wiki.osdev.org/Bochs_VBE_Extensions
*/ 

#include <system/components/bochsvbe.h>
#include <system/system.h>

using namespace Novanix;
using namespace Novanix::common;
using namespace Novanix::system;
using namespace Novanix::core;

BochsVBE::BochsVBE()
: GraphicsDevice("Bochs VBE Adapter"),
SystemComponent("BOCHS VBE", "Bochs VBE Extensions")
{ }

void WriteRegister(uint16_t IndexValue, uint16_t DataValue)
{
    outportw(VBE_DISPI_IOPORT_INDEX, IndexValue);
    outportw(VBE_DISPI_IOPORT_DATA, DataValue);
}
 
uint16_t ReadRegister(uint16_t IndexValue)
{
    outportw(VBE_DISPI_IOPORT_INDEX, IndexValue);
    return inportw(VBE_DISPI_IOPORT_DATA);
}
 
bool BochsVBE::IsAvailable()
{
    uint16_t id = ReadRegister(VBE_DISPI_INDEX_ID);
    return (id >= VBE_DISPI_ID0 && id <= VBE_DISPI_ID5);
}
 
void SetVideoMode(uint32_t Width, uint32_t Height, uint32_t BitDepth, int UseLinearFrameBuffer, int ClearVideoMemory)
{
    WriteRegister(VBE_DISPI_INDEX_ENABLE, VBE_DISPI_DISABLED);
    WriteRegister(VBE_DISPI_INDEX_XRES, Width);
    WriteRegister(VBE_DISPI_INDEX_YRES, Height);
    WriteRegister(VBE_DISPI_INDEX_BPP, BitDepth);
    WriteRegister(VBE_DISPI_INDEX_ENABLE, VBE_DISPI_ENABLED |
        (UseLinearFrameBuffer ? VBE_DISPI_LFB_ENABLED : 0) |
        (ClearVideoMemory ? 0 : VBE_DISPI_NOCLEARMEM));
}
            
bool BochsVBE::SelectBestVideoMode()
{
    if(!IsAvailable())
        return false;
    
    SetVideoMode(VBE_DISPI_MAX_XRES, VBE_DISPI_MAX_YRES, 32, true, true);

    this->width = VBE_DISPI_MAX_XRES;
    this->height = VBE_DISPI_MAX_YRES;
    this->bpp = 32;
    this->framebufferPhys = VBE_DISPI_LFB_PHYSICAL_ADDRESS;

    return true;
}