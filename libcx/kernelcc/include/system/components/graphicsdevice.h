/**
 * @author Ali Mirmohammad
 * @file graphicsdevice.h
 * @Credits Remco123
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
#ifndef __Novanix__SYSTEM__COMPONENTS__GRAPHICSDEVICE_H
#define __Novanix__SYSTEM__COMPONENTS__GRAPHICSDEVICE_H

#include <system/components/systemcomponent.h>

namespace Novanix
{
    namespace system
    {
        class GraphicsDevice
        {
        public:
            common::uint32_t width;
            common::uint32_t height;
            common::uint8_t bpp;
            common::uint32_t framebufferPhys;
            char* identifier = 0;

            GraphicsDevice(char* name);
            virtual ~GraphicsDevice();
            virtual bool SelectBestVideoMode();
            
            common::uint32_t GetBufferSize();
            
            static GraphicsDevice* GetBestDevice();
        };
    }
}

#endif