/**
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
#ifndef __ALINIX_KERNEL_KEYBOARD_DRIVERS_HPP
#define __ALINIX_KERNEL_KEYBOARD_DRIVERS_HPP

#include <alinix/types.h>

namespace alinix{
    namespace drivers{
        namespace usb{
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
            bool ContainsKey(uint8_t key, uint8_t* packet, int* pos);
        };
        }
    }
}

#endif /*__ALINIX_KERNEL_KEYBOARD_DRIVERS_HPP*/