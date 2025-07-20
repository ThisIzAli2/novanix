/**
 * @author Ali Mirmohammad
 * @file random.h
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

#ifndef __Novanix__COMMON__RANDOM_H
#define __Novanix__COMMON__RANDOM_H

#include <common/types.h>

namespace Novanix
{
    namespace common
    {
        class Random
        {
        private:
            static uint32_t next;
        public:
            static int Next(uint32_t max = 32767);
            static int Next(uint32_t min, uint32_t max);             
            static void SetSeed(uint32_t seed);
        };
    }
}

#endif