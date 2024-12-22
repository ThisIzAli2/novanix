/**
 * @file graphicdevice.hpp
 ** This file is part of AliNix.

**AliNix is free software: you can redistribute it and/or modify
**it under the terms of the GNU Affero General Public License as published by
**the Free Software Foundation, either version 3 of the License, or
**(at your option) any later version.

**AliNix is distributed in the hope that it will be useful,
**but WITHOUT ANY WARRANTY; without even the implied warranty of
**MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
**GNU Affero General Public License for more details.

**You should have received a copy of the GNU Affero General Public License
**along with AliNix. If not, see <https://www.gnu.org/licenses/>.
*/

/**
 * @abstraction:
 *  - Kernel graphic drivers for the C++ section.
*/
#ifndef __ALINIX_KERNEL_COMPONENTS_GRAPHIC_DEVICE_HPP
#define __ALINIX_KERNEL_COMPONENTS_GRAPHIC_DEVICE_HPP

#include <alinix/types.h>

class GraphicsDevice
{
public:
    uint32_t width;
    uint32_t height;
    uint8_t bpp;
    uint32_t framebufferPhys;
    char* identifier = 0;

    GraphicsDevice(char* name);
    virtual ~GraphicsDevice();
    virtual bool SelectBestVideoMode();
    
    uint32_t GetBufferSize();
    
    static GraphicsDevice* GetBestDevice();
};
#endif /*__ALINIX_KERNEL_COMPONENTS_GRAPHIC_DEVICE_HPP*/