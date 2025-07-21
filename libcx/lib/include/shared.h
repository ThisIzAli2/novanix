/**
 * @author Ali Mirmohammad
 * @file shared.h
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
#ifndef __Novanix__SHARED_H
#define __Novanix__SHARED_H

/////////////////
// Data structures shared between userspace and kernel
/////////////////

namespace Novanix
{
    #define VFS_NAME_LENGTH 255

    // Holds data about a specific process, data is readonly
    struct ProcessInfo
    {
        // PID of process
        int id;
        // Which syscall interface does this process use?
        int syscallID;
        // The amount of threads of this process
        int threads;
        // Virtual memory used by heap
        unsigned int heapMemory;
        // Is this a ring 3 process?
        bool isUserspace;
        // Is process currently blocked (main thread only)
        bool blocked;
        // Filename of process excecutable
        char fileName[32];
    };

    // Info about a item represent on the disk
    struct VFSEntry
    {
        uint32_t size;  // Size of the entry in bytes
        bool isDir;     // Is this item a directory or not?
        struct
        {
            uint8_t sec;
            uint8_t min;
            uint8_t hour;
        } creationTime; // Time file was created
        struct
        {
            uint8_t day;
            uint8_t month;
            uint16_t year;
        } creationDate; // Date time was created
        char name[VFS_NAME_LENGTH]; // Name of the file 
        // TODO: Is there a better way for buffering this?
    };

    #define KEYPACKET_START 0xFF
    enum KEYPACKET_FLAGS {
        NoFlags = 0,
        Pressed = (1<<0),
        CapsLock = (1<<1),
        NumLock = (1<<2),
        LeftShift = (1<<3),
        RightShift = (1<<4),
        LeftControl = (1<<5),
        RightControl = (1<<6),
        Alt = (1<<7)
    };

    inline KEYPACKET_FLAGS operator|(KEYPACKET_FLAGS a, KEYPACKET_FLAGS b)
    {
        return static_cast<KEYPACKET_FLAGS>(static_cast<int>(a) | static_cast<int>(b));
    }

    // Keys not present in ascii table but used by Novanix and applications
    enum SpecialKeys : uint8_t {
        EscapeKey = 27,

        // Start of custom
        CapsLockKey = 128,
        NumLockKey,
        LeftShiftKey,
        RightShiftKey,
        LeftControlKey,
        RightControlKey,
        AltKey,

        F1Key,
        F2Key,
        F3Key,
        F4Key,
        F5Key,
        F6Key,
        F7Key,
        F8Key,
        F9Key,
        F10Key,
        F11Key,
        F12Key
    };

    // Packet containing info on Keypress event
    struct KeypressPacket
    {
        uint8_t startByte; //Start of packet
        uint8_t keyCode; //keycode in integer format
        KEYPACKET_FLAGS flags; //Button state flags
    } __attribute__((packed));
}
#endif