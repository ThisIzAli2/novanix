/**
 * @author Ali Mirmohammad
 * @file random.cpp
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
#include <common/random.h>

using namespace Novanix::common;

uint32_t Random::next;

int Random::Next(uint32_t max)
{
    next = next * 1103515245 + 12345;
    return (unsigned int)(next / 65536) % (max+1);
}

int Random::Next(uint32_t min, uint32_t max)
{
    return Next(max-min) + min;
}

void Random::SetSeed(uint32_t seed)
{
    next = seed;
}