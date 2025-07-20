/**
 * @author Ali Mirmohammad
 * @file fpu.cpp
 * @Credits Remco123
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
#include <core/fpu.h>
#include <common/memoryoperations.h>

using namespace Novanix;
using namespace Novanix::common;
using namespace Novanix::core;

void FPU::Enable()
{
	uint32_t cr4;
	asm volatile ("mov %%cr4, %0" : "=r"(cr4));
	cr4 |= 0x200;
	asm volatile ("mov %0, %%cr4" :: "r"(cr4));

	////////////
	// Set Control Word
	////////////
    FPUControlWord cw;
	MemoryOperations::memset(&cw, 0, sizeof(FPUControlWord));

	cw.InvalidOperand = 1;
	cw.DenormalOperand = 1;
	cw.ZeroDevide = 1;
	cw.Overflow = 1;
	cw.Underflow = 1;
	cw.Precision = 1;

	cw.PrecisionControl = 0b11;
	cw.RoundingControl = 0b00;
	cw.InfinityControl = 0;

	asm volatile("fldcw %0" :: "m"(cw));
}