/**
 * @author Ali Mirmohammad
 * @file cpu.cpp
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
#include <core/cpu.h>
#include <system/bootconsole.h>
#include <typing.hpp>
#include <drivers/cpu.h>

using namespace Novanix;
using namespace Novanix::core;
using namespace Novanix::common;
using namespace Novanix::system;

extern "C" VOID EnableSSE();



VOID CPU::PrintVendor()
{
    uint32_t largestStandardFunc;
    char vendor[13];
    cpuid(0, &largestStandardFunc, (uint32_t*)(vendor + 0), (uint32_t *)(vendor + 8), (uint32_t *)(vendor + 4));
    vendor[12] = '\0';

    BootConsole::Write("CPU Vendor: "); BootConsole::WriteLine(vendor);
}

VOID CPU::EnableFeatures()
{
    uint32_t eax, ebx, ecx, edx;

    cpuid(0x01, &eax, &ebx, &ecx, &edx);

    if (edx & EDX_SSE2) { 
        BootConsole::WriteLine("CPU Has SSE2");

        EnableSSE();
    }
    else
    {
        BootConsole::WriteLine("Error: CPU has no SSE2. This is needed");

        while(1);
    }

    if(edx & EDX_FXSR) {
        BootConsole::WriteLine("CPU Has FXSR");
    }
    else
    {
        BootConsole::WriteLine("Error: CPU has no FXSR. This is needed");

        while(1);
    } 
}