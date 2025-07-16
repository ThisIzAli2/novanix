/**
 * @author Ali Mirmohammad
 * @file tss.h
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
#ifndef __Novanix__CORE__TSS_H
#define __Novanix__CORE__TSS_H

#include <common/types.h>
#include <common/memoryoperations.h>
#include <core/gdt.h>

namespace Novanix
{
    namespace core
    {
        struct TSSEntry {
            common::uint32_t prevTss;
            common::uint32_t esp0;
            common::uint32_t ss0;
            common::uint32_t esp1;
            common::uint32_t ss1;
            common::uint32_t esp2;
            common::uint32_t ss2;
            common::uint32_t cr3;
            common::uint32_t eip;
            common::uint32_t eflags;
            common::uint32_t eax;
            common::uint32_t ecx;
            common::uint32_t edx;
            common::uint32_t ebx;
            common::uint32_t esp;
            common::uint32_t ebp;
            common::uint32_t esi;
            common::uint32_t edi;
            common::uint32_t es;
            common::uint32_t cs;
            common::uint32_t ss;
            common::uint32_t ds;
            common::uint32_t fs;
            common::uint32_t gs;
            common::uint32_t ldt;
            common::uint16_t trap;
            common::uint16_t iomap;
        };

        class TSS
        {
        public:
            static void Install(common::uint32_t idx, common::uint32_t kernelSS, common::uint32_t kernelESP);
            static void SetStack(common::uint32_t kernelSS, common::uint32_t kernelESP);
            static TSSEntry* GetCurrent();
        };
    }
}

#endif