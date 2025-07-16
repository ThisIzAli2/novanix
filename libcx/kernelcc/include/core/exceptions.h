/**
 * @author Ali Mirmohammad
 * @file exceptions.h
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

#ifndef __Novanix__CORE__EXCEPTIONS_H
#define __Novanix__CORE__EXCEPTIONS_H

#include <common/types.h>
#include <system/bootconsole.h>
#include <common/convert.h>
#include <core/idt.h>

namespace Novanix
{
    namespace core
    {
        struct SelectorErrorCode
        {
            common::uint8_t External : 1;
            common::uint8_t Table : 2;
            common::uint16_t TableIndex : 13;
        } __attribute__((packed));
        

        class Exceptions
        {
        private:
            static common::uint32_t DivideByZero(common::uint32_t esp);
            static common::uint32_t GeneralProtectionFault(common::uint32_t esp);
            static common::uint32_t PageFault(common::uint32_t esp);
            static common::uint32_t TrapException(common::uint32_t esp);
            static common::uint32_t FloatingPointException(common::uint32_t esp);
            static common::uint32_t StackSegmentFault(common::uint32_t esp);
            static void ShowStacktrace(common::uint32_t esp);
        public:
            static common::uint32_t HandleException(common::uint32_t number, common::uint32_t esp);
            
            /*
             * Enables the automatic pagefault fix procedure
             * Warning: Only use when trying to access physical memory with no way to map it.
            */
            static void EnablePagefaultAutoFix();
            /*
             * Disables the automatic pagefault fix procedure
            */
            static void DisablePagefaultAutoFix();
        };
    }
}

#endif