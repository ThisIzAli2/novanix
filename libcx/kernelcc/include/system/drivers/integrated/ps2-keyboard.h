/**
 * @author Ali Mirmohammad
 * @file ps2-keyboard.h
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
#ifndef __Novanix__SYSTEM__DRIVERS__PS2KEYBOARD_H
#define __Novanix__SYSTEM__DRIVERS__PS2KEYBOARD_H

#include <system/drivers/driver.h>
#include <system/interruptmanager.h>
#include <system/memory/fifostream.h>
#include <system/input/keyboard.h>

namespace Novanix
{
    namespace system
    {
        namespace drivers
        {
            #define PS2_DATA 0x60
            #define PS2_STATUS 0x64
            #define PS2_COMMAND 0x64

            class PS2KeyboardDriver : public InterruptHandler, public Keyboard, public Driver, public FIFOStream
            {
            public:
                PS2KeyboardDriver();

                bool Initialize();
                common::uint32_t HandleInterrupt(common::uint32_t esp);

                // Update LED's on a keyboard device
                void UpdateLEDS() override;
            };
        }
    }
}

#endif