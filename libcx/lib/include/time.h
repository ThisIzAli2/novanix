/**
 * @author Ali Mirmohammad
 * @file time.h
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
#ifndef __Novanix__TIME_H
#define __Novanix__TIME_H

#include <types.h>

namespace Novanix
{
    class Time
    {
    public:
        /**
         * Make this thread sleep for a specific amount of ms
        */
        static void Sleep(uint32_t ms);
        /**
         * Get the current amount of ticks from the timer
        */
        static uint64_t Ticks();
    };
}

#endif