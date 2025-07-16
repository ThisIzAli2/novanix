/**
 * @author Ali Mirmohammad
 * @file pit.h
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
#ifndef __Novanix__CORE__PIT_H
#define __Novanix__CORE__PIT_H

#include <system/interruptmanager.h>
#include <system/components/systemcomponent.h>
#include <core/port.h>

namespace Novanix
{
    namespace system
    {
        #define PIT_FREQUENCY 1000

        class PIT : public SystemComponent, public InterruptHandler
        {
        private:
            volatile common::uint64_t timer_ticks;
        public:
            PIT();

            common::uint32_t HandleInterrupt(common::uint32_t esp);
            void Sleep(common::uint32_t ms);

            //PCSpeaker
            void PlaySound(common::uint32_t nFrequence);
            void NoSound();
            void Beep();
            void Beep(common::uint32_t freq);
            void Beep(common::uint32_t freq, common::uint32_t duration);

            common::uint64_t Ticks();
        };
    }
}

#endif