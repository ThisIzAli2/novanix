/**
 * @author Ali Mirmohammad
 * @file keyboard.hpp
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

#ifndef __ALINIX_KERNEL_SYSTEM_DRIVER_USB_KEYBOARD_HPP
#define __ALINIX_KERNEL_SYSTEM_DRIVER_USB_KEYBOARD_HPP


#ifndef __cplusplus
# error "This file must be compiled with C++"

#endif  /* !__cplusplus */

#include <alinix/keyboard.h>
#include <alinix/types.h>

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

#endif //__ALINIX_KERNEL_SYSTEM_DRIVER_USB_KEYBOARD_HPP