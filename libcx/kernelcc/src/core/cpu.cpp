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

/**
 * NOTE: Use __cpuid here, not cpuid
 */
VOID print_cpu_info(){
    uint32_t eax, ebx, ecx, edx;

    // Get CPU vendor
    char vendor[13];
    __cpuid(0, 0, &eax, &ebx, &ecx, &edx);
    MemoryOperations::memcpy(&vendor[0], &ebx, 4);
    MemoryOperations::memcpy(&vendor[4], &edx, 4);
    MemoryOperations::memcpy(&vendor[8], &ecx, 4);
    vendor[12] = '\0';
    printk(VGA_WHITE,"CPU Vendor: %s\n",1,vendor);

    // Get CPU features, family, model, stepping
    __cpuid(1, 0, &eax, &ebx, &ecx, &edx);

    uint8_t stepping = eax & 0xF;
    uint8_t model = (eax >> 4) & 0xF;
    uint8_t family = (eax >> 8) & 0xF;
    uint8_t ext_model = (eax >> 16) & 0xF;
    uint8_t ext_family = (eax >> 20) & 0xFF;

    if (family == 6 || family == 15)
        model += (ext_model << 4);
    if (family == 15)
        family += ext_family;

    printk(VGA_WHITE,"CPU Family: %u\n", 1,family);
    printk(VGA_WHITE,"CPU Model: %u\n", 1,family);
    printk(VGA_WHITE,"CPU Stepping: %u\n", 1,stepping);

    // Feature detection
    if (edx & (1 << 23)) printk(VGA_WHITE,"MMX supported\n",1);
    if (edx & (1 << 25)) printk(VGA_WHITE,"SSE supported\n",1);
    if (edx & (1 << 26)) printk(VGA_WHITE,"SSE2 supported\n",1);
    if (ecx & (1 << 0))  printk(VGA_WHITE,"SSE3 supported\n",1);
    if (ecx & (1 << 9))  printk(VGA_WHITE,"SSSE3 supported\n",1);
    if (ecx & (1 << 19)) printk(VGA_WHITE,"SSE4.1 supported\n",1);
    if (ecx & (1 << 20)) printk(VGA_WHITE,"SSE4.2 supported\n",1);
    if (ecx & (1 << 28)) printk(VGA_WHITE,"AVX supported\n",1);

    // Full CPU brand string
    char brand[49];
    for (int i = 0; i < 3; i++) {
        __cpuid(0x80000002 + i, 0, &eax, &ebx, &ecx, &edx);
        MemoryOperations::memcpy(brand + i * 16, &eax, 4);
        MemoryOperations::memcpy(brand + i * 16 + 4, &ebx, 4);
        MemoryOperations::memcpy(brand + i * 16 + 8, &ecx, 4);
        MemoryOperations::memcpy(brand + i * 16 + 12, &edx, 4);
    }
    brand[48] = '\0';
    printk(VGA_WHITE,"CPU Brand: %s\n", 1,brand);
}