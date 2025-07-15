/**
 * @author Ali Mirmohammad
 * @file graphicsdevice.cpp
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
#include <system/components/graphicsdevice.h>
#include <system/components/bochsvbe.h>
#include <system/components/vesa.h>
#include <system/system.h>

using namespace Novanix;
using namespace Novanix::common;
using namespace Novanix::system;

GraphicsDevice::GraphicsDevice(char* name)
{
    this->width = 0;
    this->height = 0;
    this->bpp = 0;
    this->identifier = name;
}

GraphicsDevice::~GraphicsDevice()
{
    
}

bool GraphicsDevice::SelectBestVideoMode()
{
    return false;
}

uint32_t GraphicsDevice::GetBufferSize()
{
	return this->width * this->height * (this->bpp/8);
}

//Select the best graphics device for the situation
GraphicsDevice* GraphicsDevice::GetBestDevice()
{
    #if BOCHS_GFX_HACK
    if(BochsVBE::IsAvailable() && System::isBochs)
    {
        //BootConsole::Write(" BochsVBE");
        return new BochsVBE();
    }
    #endif
    
    //BootConsole::Write(" VESA");
    return new VESA(System::vm86Manager);
}