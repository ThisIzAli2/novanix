/**
 * @author Ali Mirmohammad
 * @file ipc.cpp
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
#include <ipc.h>
#include <proc.h>
#include <string.h>

using namespace Novanix;

int Novanix::IPCSend(int dest, int type, unsigned int arg1, unsigned int arg2, unsigned int arg3, unsigned int arg4, unsigned int arg5, unsigned int arg6)
{
    //Create IPCMessage
    IPCMessage message;
    message.dest = dest;
    message.type = type;
    message.source = Process::ID;
    
    //Copy args
    message.arg1 = arg1;
    message.arg2 = arg2;
    message.arg3 = arg3;
    message.arg4 = arg4;
    message.arg5 = arg5;
    message.arg6 = arg6;
    
    return IPCSend(message);
}

int Novanix::IPCSend(IPCMessage message)
{
    return DoSyscall(SYSCALL_IPC_SEND, (uint32_t)&message);
}

int Novanix::IPCAvailable()
{
    return DoSyscall(SYSCALL_IPC_AVAILABLE);
}

IPCMessage Novanix::ICPReceive(int fromID, int* errOut, int type)
{
    IPCMessage result;
    DoSyscall(SYSCALL_IPC_RECEIVE, (uint32_t)&result, fromID, (uint32_t)errOut, type);
    return result;
}