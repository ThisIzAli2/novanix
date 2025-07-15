/**
 * @author Ali Mirmohammad
 * @file keyboard.cpp
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
#include <system/input/keyboard.h>
#include <system/system.h>

using namespace Novanix;
using namespace Novanix::common;
using namespace Novanix::system;

Keyboard::Keyboard(KeyboardType type)
{
    this->type = type;
    MemoryOperations::memset(&this->status, 0, sizeof(this->status));
}

void Keyboard::UpdateLEDS()
{
    Log(Error, "Virtual function called directly %s:%d", __FILE__, __LINE__);
}

bool Keyboard::ContainsKey(uint8_t key, uint8_t* packet, int* pos)
{
    for(int i = 2; i < 8; i++)
        if(packet[i] == key) { *pos = i; return true; }
    return false;
}