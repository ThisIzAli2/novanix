/**
 * @author Ali Mirmohammad
 * @file lock.cpp
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
#include <system/tasking/lock.h>
#include <system/system.h>

using namespace Novanix;
using namespace Novanix::system;

extern "C" int TestAndSet(int newValue, int* ptr);

MutexLock::MutexLock()
{
    this->value = 0;
}
void MutexLock::Lock()
{
    while (TestAndSet(1, &this->value) == 1) {
        if(System::scheduler && System::scheduler->Enabled)
            System::scheduler->ForceSwitch();
        else
            asm ("pause");
    }
}
void MutexLock::Unlock()
{
    this->value = 0;
}