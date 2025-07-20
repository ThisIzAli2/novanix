/**
 * @author Ali Mirmohammad
 * @file print.cpp
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
#include <common/print.h>

using namespace Novanix;
using namespace Novanix::system;
using namespace Novanix::common;
using namespace Novanix::core;

void Print::printfHex(uint8_t key)
{
    char *foo = "00";
    char *hex = "0123456789ABCDEF";
    foo[0] = hex[(key >> 4) & 0xF];
    foo[1] = hex[key & 0xF];
    system::BootConsole::Write(foo);
}
void Print::printfHex16(uint16_t key)
{
    printfHex((key >> 8) & 0xFF);
    printfHex(key & 0xFF);
}
void Print::printfHex32(uint32_t key)
{
    printfHex((key >> 24) & 0xFF);
    printfHex((key >> 16) & 0xFF);
    printfHex((key >> 8) & 0xFF);
    printfHex(key & 0xFF);
}
void Print::printbits(uint8_t key)
{
    for (unsigned int bit = 0; bit < (sizeof(key)*8); bit++)
    {
        BootConsole::Write(Convert::IntToString(key & 0x01));
        key = key >> 1;
    }
}
void Print::printbits(uint16_t key)
{
    for (unsigned int bit = 0; bit < (sizeof(key)*8); bit++)
    {
        BootConsole::Write(Convert::IntToString(key & 0x01));
        key = key >> 1;
    }
}
void Print::printbits(uint32_t key)
{
    for (unsigned int bit = 0; bit < (sizeof(key)*8); bit++)
    {
        BootConsole::Write(Convert::IntToString(key & 0x01));
        key = key >> 1;
    }
}
void Print::printbits(uint64_t key)
{
    for (unsigned int bit = 0; bit < (sizeof(key)*8); bit++)
    {
        BootConsole::Write(Convert::IntToString(key & 0x01));
        key = key >> 1;
    }
}