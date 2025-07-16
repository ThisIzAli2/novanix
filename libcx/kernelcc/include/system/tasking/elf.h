/**
 * @author Ali Mirmohammad
 * @file elf.h
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
#ifndef __Novanix__SYSTEM__ELFLOADER_H
#define __Novanix__SYSTEM__ELFLOADER_H

#include <common/types.h>
#include <system/tasking/process.h>

namespace Novanix
{
    namespace system
    {
        #define ELFMAG0   0x7f
        #define ELFMAG1   'E'
        #define ELFMAG2   'L'
        #define ELFMAG3   'F'

        struct ElfHeader {
            unsigned char e_ident[16];
            common::uint16_t e_type;
            common::uint16_t e_machine;
            common::uint32_t e_version;
            common::uint32_t e_entry;
            common::uint32_t e_phoff;
            common::uint32_t e_shoff;
            common::uint32_t e_flags;
            common::uint16_t e_ehsize;
            common::uint16_t e_phentsize;
            common::uint16_t e_phnum;
            common::uint16_t e_shentsize;
            common::uint16_t e_shnum;
            common::uint16_t e_shstrndx;
        } __attribute__((packed));

        struct ElfSectionHeader {
            common::uint32_t sh_name;
            common::uint32_t sh_type;
            common::uint32_t sh_flags;
            common::uint32_t sh_addr;
            common::uint32_t sh_offset;
            common::uint32_t sh_size;
            common::uint32_t sh_link;
            common::uint32_t sh_info;
            common::uint32_t sh_addralign;
            common::uint32_t sh_entsize;
        } __attribute__((packed));

        struct ElfProgramHeader {
            common::uint32_t p_type;
            common::uint32_t p_offset;
            common::uint32_t p_vaddr;
            common::uint32_t p_paddr;
            common::uint32_t p_filesz;
            common::uint32_t p_memsz;
            common::uint32_t p_flags;
            common::uint32_t p_align;
        } __attribute__((packed));
    }
}

#endif