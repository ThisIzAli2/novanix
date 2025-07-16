/**
 * @author Ali Mirmohammad
 * @file rtc.h
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
#ifndef __Novanix__SYSTEM__COMPONENTS__RTC_H
#define __Novanix__SYSTEM__COMPONENTS__RTC_H

#include <core/port.h>
#include <system/components/systemcomponent.h>

namespace Novanix
{
    namespace system
    {
        #define CURRENT_YEAR 2020

        class RTC : public SystemComponent
        {
        private:
            bool UpdateInProgress();
            common::uint8_t ReadRegister(int reg);
        public:
            RTC();

            common::uint32_t GetSecond();
            common::uint32_t GetMinute();
            common::uint32_t GetHour();
            common::uint32_t GetDay();
            common::uint32_t GetMonth();
            common::uint32_t GetYear();
        };  
    }
}

#endif