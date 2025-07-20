/**
 * @author Ali Mirmohammad
 * @file keyboard.h
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
*/#ifndef __Novanix__SYSTEM__INPUT__KEYBOARD_H
#define __Novanix__SYSTEM__INPUT__KEYBOARD_H

#include <common/types.h>

namespace Novanix
{
    namespace system
    {
        // Structure for modifier keys that are keyboard specific
        struct InternalKeyboardStatus
        {
            bool LeftShift;
            bool RightShift;

            bool Alt;
            bool AltGr;
            
            bool LeftControl;
            bool RightControl;
        };

        // Structure for shared modifier keys between keyboards
        struct KeyboardStatus
        {
            bool CapsLock;
            bool NumLock;
        };
        
        // Types of keyboards currently supported
        enum KeyboardType
        {
            PS2,
            USB
        };

        // Interface for providing a common access for all keyboard devices
        class Keyboard
        {
        public:
            KeyboardType type;
            InternalKeyboardStatus status;
        public:
            Keyboard(KeyboardType type);

            // Update LED's on a keyboard device
            virtual void UpdateLEDS();
            
            // Checks if the buffer contains the given key, also returns position of key
            bool ContainsKey(common::uint8_t key, common::uint8_t* packet, int* pos);
        };
    }
}

#endif