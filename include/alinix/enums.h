/**
 * @author Ali Mirmohammad
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
 * @file enums.h
 * Abstract:
 *      - Provide utility for the kernel enums
*/

#ifndef __ALINIX_KERNEL_ENUMS_HEADER_H
#define __ALINIX_KERNEL_ENUMS_HEADER_H

typedef enum priority{
    /*A class that defined a proccess priority*/
    LOWEST = -150,
    LOWER = -50,
    LOW = -10,
    NORMAL = 0,
    HIGH = 10,
    HIGHER = 50,
    HIGHEST = 150
}priority_t;

enum ScreenMode_t
{
    TextMode,
    GraphicsMode
};

enum PowerRequest
{
    None,
    Shutdown,
    RebootR
    // TODO Change here to reboot maybe
};

enum EndpointDirection 
{
    Out,
    In
};

enum EndpointType 
{
    Control,
    Isochronous,
    Bulk,
    Interrupt
};

enum COMPort {
    COM1 = 0x3F8,
    COM2 = 0x2F8,
    COM3 = 0x3E8,
    COM4 = 0x2E8
};

typedef enum {
    DISK_TYPE_UNKNOWN,
    DISK_TYPE_HDD,
    DISK_TYPE_SSD
} DiskType;

enum ThreadState
{
    Blocked,
    Ready,
    Stopped,
    Started
};



enum BlockedState
{
    Unkown,
    SleepMS,
    ReceiveIPC
};

#endif /*__ALINIX_KERNEL_ENUMS_HEADER_H*/