/**
 * @file mmio.hpp
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
 *  - Provides net util for C++ section.
*/


#ifndef __ALINIX_KERNEL_CPP_MMIO_HPP
#define __ALINIX_KERNEL_CPP_MMIO_HPP

#include "port.hpp"
#include <alinix/types.h>


class MMIOUtils
{
    public:
        static uint8_t read8 (uint64_t p_address);
        static uint16_t read16 (uint64_t p_address);
        static uint32_t read32 (uint64_t p_address);
        static uint64_t read64 (uint64_t p_address);
        static void write8 (uint64_t p_address,uint8_t p_value);
        static void write16 (uint64_t p_address,uint16_t p_value);
        static void write32 (uint64_t p_address,uint32_t p_value);
        static void write64 (uint64_t p_address,uint64_t p_value);
};
 
 
uint8_t MMIOUtils::read8 (uint64_t p_address)
{
    return *((volatile uint8_t*)(p_address));
}
uint16_t MMIOUtils::read16 (uint64_t p_address)
{
    return *((volatile uint16_t*)(p_address));
 
}
uint32_t MMIOUtils::read32 (uint64_t p_address)
{
    return *((volatile uint32_t*)(p_address));
 
}
uint64_t MMIOUtils::read64 (uint64_t p_address)
{
    return *((volatile uint64_t*)(p_address));    
}
void MMIOUtils::write8 (uint64_t p_address,uint8_t p_value)
{
    (*((volatile uint8_t*)(p_address)))=(p_value);
}
void MMIOUtils::write16 (uint64_t p_address,uint16_t p_value)
{
    (*((volatile uint16_t*)(p_address)))=(p_value);    
}
void MMIOUtils::write32 (uint64_t p_address,uint32_t p_value)
{
    (*((volatile uint32_t*)(p_address)))=(p_value);
 
}
void MMIOUtils::write64 (uint64_t p_address,uint64_t p_value)
{
    (*((volatile uint64_t*)(p_address)))=(p_value);    
}


#endif /*__ALINIX_KERNEL_CPP_MMIO_HPP*/