/**
 * @author Ali Mirmohammad
 * @file api.cpp
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
#include <api.h>

#include <syscall.h>
#include <log.h>
#include <proc.h>

using namespace Novanix;

void API::Initialize()
{
    //Call kernel to set this process as a Novanix process
    Process::ID = DoSyscall(SYSCALL_SET_Novanix_LIB);

    Log(Info, "Novanix API Initialized for this process");
}