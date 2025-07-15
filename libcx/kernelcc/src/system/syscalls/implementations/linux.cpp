/**
 * @author Ali Mirmohammad
 * @file linux.cpp
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
#include <system/syscalls/implementations/linux.h>

#include <system/system.h>

using namespace Novanix;
using namespace Novanix::common;
using namespace Novanix::core;
using namespace Novanix::system;

CPUState* LinuxSyscalls::HandleSyscall(CPUState* state)
{
    switch (state->EAX)
    {
        case 0xFFFF: //We use this systemcall for setting the Novanix Syscall implementation for this process since linux is the default one
            //From now on this uses Novanix Systemcalls
            System::scheduler->CurrentProcess()->syscallID = 1;
            //Return a succes
            state->EAX = System::scheduler->CurrentProcess()->id; //Return the pid
            break;
    
        default:
            state->EAX = 0;
            break;
    }

    return state;
}