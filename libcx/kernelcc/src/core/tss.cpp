/**
 * @author Ali Mirmohammad
 * @file tss.cpp
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
#include <core/tss.h>

using namespace Novanix;
using namespace Novanix::common;
using namespace Novanix::core;

static TSSEntry tss;

extern "C" void flush_tss();

void TSS::Install(uint32_t idx, uint32_t kernelSS, uint32_t kernelESP)
{
	MemoryOperations::memset(&tss, 0, sizeof(TSSEntry));

    //! install TSS descriptor
	uint32_t base = (uint32_t) &tss;

	//! install descriptor
	GlobalDescriptorTable::SetDescriptor (idx, base, base + sizeof (TSSEntry), 0xE9, 0);

	//! initialize TSS
    MemoryOperations::memset ((void*) &tss, 0, sizeof (TSSEntry));

	//! set stack and segments
	tss.ss0 = kernelSS;
	tss.esp0 = kernelESP;
	tss.iomap = sizeof(TSSEntry);

	//! flush tss
	flush_tss();
}

void TSS::SetStack(uint32_t kernelSS, uint32_t kernelESP)
{
    tss.ss0 = kernelSS;
    tss.esp0 = kernelESP;
}

TSSEntry* TSS::GetCurrent()
{
	return &tss;
}