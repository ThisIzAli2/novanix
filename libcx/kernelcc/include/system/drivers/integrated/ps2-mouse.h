/**
 * @author Ali Mirmohammad
 * @file ps2-mouse.h
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
#ifndef __Novanix__SYSTEM__DRIVERS__PS2MOUSE_H
#define __Novanix__SYSTEM__DRIVERS__PS2MOUSE_H

#include <system/drivers/driver.h>
#include <system/interruptmanager.h>

namespace Novanix
{
    namespace system
    {
        namespace drivers
        {
            struct MousePacket
            {
                unsigned char LeftBTN : 1;
                unsigned char RightBTN : 1;
                unsigned char MiddleBTN : 1;
                unsigned char Always1 : 1;
                unsigned char Xsign : 1;
                unsigned char Ysign : 1;
                unsigned char Xoverflow : 1;
                unsigned char Yoverflow : 1;

                signed char XMovement;
                signed char YMovement;
                signed char ZMovement; //if MouseID == 3
            };
            

            class PS2MouseDriver : public InterruptHandler, public Driver
            {
            private:
                #define MOUSE_DATA 0x60
                #define MOUSE_COMMAND 0x64
                #define MOUSE_ACK 0xFA

                common::uint8_t MouseID = 0;
                common::uint8_t MouseCycle = 0;
                signed char* packetBuffer;

                bool ready = false;
            public:
                PS2MouseDriver();

                bool Initialize();
                common::uint32_t HandleInterrupt(common::uint32_t esp);

                /**
                 * Enable the scrollwheel for this mouse, returns true when succeeded
                */
                bool EnableScrollWheel();
                /**
                 * Valid values: 10,20,40,60,80,100,200 
                */
                bool SetSampleRate(common::uint8_t value);
                /**
                 * Handle a packet send by the mouse
                */
                void ProcessPacket();
            };
        }
    }
}

#endif