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
/**
 * MIT License

Copyright (c) 2020 Remco123

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/
#include <system/serialport.h>

using namespace CactusOS;
using namespace CactusOS::common;
using namespace CactusOS::core;
using namespace CactusOS::system;

/*/////////////////
// Static variable initialisations
/*/////////////////
COMPort Serialport::PortAddress = COMPort::COM1;
bool Serialport::Initialized = false;

/*/////////////////
// Private functions
/*/////////////////
int Serialport::SerialReceiveReady()
{
    return inportb(PortAddress + 5) & 1;
}
int Serialport::SerialSendReady()
{
    return inportb(PortAddress + 5) & 0x20;
}

/*/////////////////
// Public functions
/*/////////////////
char Serialport::Read()
{
    while (SerialReceiveReady() == 0);

    return inportb(PortAddress);
}
void Serialport::Write(char a)
{
    while (SerialSendReady() == 0);

    outportb(PortAddress, a);
}
void Serialport::WriteStr(char* str)
{
    for(int i = 0; str[i] != '\0'; ++i)
        Write(str[i]);
}

void Serialport::Init(COMPort port)
{
    Serialport::PortAddress = port;

    outportb(PortAddress + 1, 0x00);    // Disable all interrupts
    outportb(PortAddress + 3, 0x80);    // Enable DLAB (set baud rate divisor)
    outportb(PortAddress + 0, 0x03);    // Set divisor to 3 (lo byte) 38400 baud
    outportb(PortAddress + 1, 0x00);    //                  (hi byte)
    outportb(PortAddress + 3, 0x03);    // 8 bits, no parity, one stop bit
    outportb(PortAddress + 2, 0xC7);    // Enable FIFO, clear them, with 14-byte threshold
    outportb(PortAddress + 4, 0x0B);    // IRQs enabled, RTS/DSR set

    Serialport::Initialized = true;
}