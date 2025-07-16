/**
 * @author Ali Mirmohammad
 * @file proc.cpp
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
#include <proc.h>
#include <listing.h>

using namespace Novanix;

int Process::ID = -1;
int Process::numThreads = 1;
SharedSystemInfo* Process::systemInfo = 0;

int Process::Run(const char* path, bool block)
{
    return DoSyscall(SYSCALL_RUN_PROC, (uint32_t)path, (uint32_t)block);
}
bool Process::CreateSharedMemory(int proc2ID, uint32_t virtStart1, uint32_t virtStart2, uint32_t len)
{
    return DoSyscall(SYSCALL_CREATE_SHARED_MEM, proc2ID, virtStart1, virtStart2, len);
}
bool Process::CreateSharedMemory(int proc2ID, uint32_t virtStart, uint32_t len)
{
    return CreateSharedMemory(proc2ID, virtStart, virtStart, len);
}
bool Process::DeleteSharedMemory(int proc2ID, uint32_t virtStart, uint32_t len)
{
    return DeleteSharedMemory(proc2ID, virtStart, virtStart, len);
}
bool Process::DeleteSharedMemory(int proc2ID, uint32_t virtStart1, uint32_t virtStart2, uint32_t len)
{
    return DoSyscall(SYSCALL_REMOVE_SHARED_MEM, proc2ID, virtStart1, virtStart2, len);
}
void Process::CreateThread(void (*entryPoint)(), bool switchTo)
{
    DoSyscall(SYSCALL_START_THREAD, (uint32_t)entryPoint, switchTo);
    Process::numThreads++;
}
void Process::Yield()
{
    DoSyscall(SYSCALL_YIELD);
}
void Process::SetScheduler(bool active)
{
    DoSyscall(SYSCALL_SET_SCHEDULER, active);
}
void Process::WriteStdOut(char byte)
{
    char bytes[1];
    bytes[0] = byte;
    DoSyscall(SYSCALL_WRITE_STDIO, (uint32_t)bytes, 1);
}
void Process::WriteStdOut(char* bytes, int length)
{
    DoSyscall(SYSCALL_WRITE_STDIO, (uint32_t)bytes, length);
}
char Process::ReadStdIn()
{
    return DoSyscall(SYSCALL_READ_STDIO);
}
void Process::BindSTDIO(int fromID, int toID)
{
    DoSyscall(SYSCALL_REDIRECT_STDIO, fromID, toID);
}
int Process::StdInAvailable()
{
    return DoSyscall(SYSCALL_STDIO_AVAILABLE);
}
bool Process::Active(int pid)
{
    return DoSyscall(SYSCALL_PROC_EXIST, pid);
}
void Process::Unblock(int procPID, int thread)
{
    DoSyscall(SYSCALL_UNBLOCK, procPID, thread);
}