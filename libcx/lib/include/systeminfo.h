/**
 * @author Ali Mirmohammad
 * @file systeminfo.h
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
#ifndef __Novanix__SYSTEMINFO_H
#define __Novanix__SYSTEMINFO_H

#ifdef NovanixKERNEL
#include <common/types.h>
#else
#include <types.h>
#endif

namespace Novanix
{
    #define SYSTEM_INFO_ADDR 0xBFFEE000

    enum SIPropertyIdentifier
    {
        String,
        Index
    };

    class SIPropertyProvider
    {
    public:
        char* id = 0;
        int index = 0;
        SIPropertyIdentifier type = String;

        SIPropertyProvider* parent = 0;
    public:
        SIPropertyProvider(char* property);
        SIPropertyProvider(int index);

        // Collection functions

        // Get Count of items present in this collection
        int size();

        // Get specific property of collection
        SIPropertyProvider operator[](const int index);
        SIPropertyProvider operator[](const char* element);

        template<typename T>
        T receiveValue(const bool getsize) const;

        template<typename T>
        T receiveBuffer() const;

        // We are a property ourself
        operator int() const;       // Receive this property as integer
        operator bool() const;      // Receive this property as boolean
        operator double() const;    // Receive this property as double
        operator char*() const;     // Receive this property as string
        operator uint64_t() const;  // Receive this property as unsigned long
        operator uint32_t() const;  // Receive this property as unsigned int
        operator uint16_t() const;  // Receive this property as unsigned word
        operator uint8_t() const;  // Receive this property as unsigned char
    } __attribute__((packed));

    // A class for managing all information known about the current system
    // With this a application can monitor the system
    class SystemInfo
    {
    public:
        // All properties of the current system
        // Things like connected disks and usbdevices
        static SIPropertyProvider Properties;

        // Request System info to be mapped into address space
        // Addres is SYSTEM_INFO_ADDR which is 2 pages below user-stack
        static bool RequestSystemInfo();
    };

    // This struct can be shared between the kernel and userspace processes
    struct SharedSystemInfo
    {
        unsigned int MouseX;
        unsigned int MouseY;
        signed int   MouseZ;

        bool MouseLeftButton;
        bool MouseRightButton;
        bool MouseMiddleButton;
    } __attribute__((packed));
}

#endif