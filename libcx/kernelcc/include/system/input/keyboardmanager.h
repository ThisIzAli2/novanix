/**
 * @author Ali Mirmohammad
 * @file keyboardmanager.h
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
#ifndef __Novanix__SYSTEM__INPUT__KEYBOARDMANAGER_H
#define __Novanix__SYSTEM__INPUT__KEYBOARDMANAGER_H

#include <system/input/keyboard.h>
#include <common/list.h>
#include <system/memory/fifostream.h>

namespace Novanix
{
    namespace system
    {
        // Class responsable for managing all keyboard devices present on the system
        // Also provides a stream interface to read keystrokes 
        class KeyboardManager : public FIFOStream
        {
        public:
            // List of all keyboards present on system
            List<Keyboard*> keyboards;

            // Status of all keyboards
            KeyboardStatus sharedStatus;
        private:
            uint8_t ConvertToPS2(uint32_t key);
        public:
            KeyboardManager();

            // Handle a keypress or a change in modifier keys
            void HandleKeyChange(Keyboard* src, uint32_t key, bool pressed);
        };
    }
}

#endif