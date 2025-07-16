/**
 * @author Ali Mirmohammad
 * @file time.cpp
 * Credits Remco123
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
#include <time.h>

#include <syscall.h>

using namespace Novanix;

void Time::Sleep(uint32_t ms)
{
    DoSyscall(SYSCALL_SLEEP_MS, ms);
}

uint64_t Time::Ticks()
{
    uint64_t r = 0;
    DoSyscall(SYSCALL_GET_TICKS, (uint32_t)&r);
    return r;
}