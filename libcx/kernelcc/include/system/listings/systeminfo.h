/**
 * @author Ali Mirmohammad
 * @file systeminfo.h
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
#ifndef __Novanix__SYSTEM__LISTINGS__SYSTEMINFO_H
#define __Novanix__SYSTEM__LISTINGS__SYSTEMINFO_H

#include <common/types.h>

namespace Novanix
{
    namespace system
    {
        struct SIBIOS
        {
            char* vendor = "N/A";
            char* version = "N/A";
            char* releaseDate = "N/A";
        };

        struct SISYSTEM
        {
            char* manufacturer = "N/A";
            char* product = "N/A";
            char* version = "N/A";
            char* serial = "N/A";
            char* sku = "N/A";
            char* family = "N/A";  
        };

        struct SIENCLOSURE
        {
            char* manufacturer = "N/A";
            char* version = "N/A";
            char* serial = "N/A";
            char* sku = "N/A";
        };

        struct SIPROCESSOR
        {
            char* socket = "N/A";
            char* manufacturer = "N/A";
            char* version = "N/A";
        };       

        class SystemInfoManager
        {
        public:
            static SIBIOS       bios;
            static SISYSTEM     system;
            static SIENCLOSURE  enclosure;
            static SIPROCESSOR  processor;
        public:
            // Handle a request from a syscall to get information about the system
            static bool HandleSysinfoRequest(void* arrayPointer, int count, common::uint32_t retAddr, bool getSize);
        };
    }
}

#endif