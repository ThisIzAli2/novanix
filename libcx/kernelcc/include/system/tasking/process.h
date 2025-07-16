/**
 * @author Ali Mirmohammad
 * @file process.h
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
#ifndef __CACTOSOS__SYSTEM__TASKING__PROCESS_H
#define __CACTOSOS__SYSTEM__TASKING__PROCESS_H

#include <system/tasking/thread.h>
#include <common/list.h>
#include <common/types.h>
#include <../../lib/include/ipc.h>
#include <system/memory/stream.h>

namespace Novanix
{
    namespace system
    {
        class SymbolDebugger;
        
        enum ProcessState
        {
            Active
        };

        #define PROC_USER_HEAP_SIZE 1_MB //1 MB heap space for processes, and of course more if needed.

        struct Thread;

        struct Process
        {
            int id;
            int syscallID;
            bool isUserspace;
            char* args;
            ProcessState state;
            List<Thread*> Threads;
            common::uint32_t pageDirPhys;
            struct Excecutable
            {
                common::uint32_t memBase;
                common::uint32_t memSize;
            } excecutable;
            
            struct Heap
            {
                common::uint32_t heapStart;
                common::uint32_t heapEnd;
            } heap;
            List<Novanix::IPCMessage> ipcMessages;

            Stream* stdInput;
            Stream* stdOutput;

            // For Debuging
            char fileName[32];

            // Debugger assigned to this process
            SymbolDebugger* symDebugger = 0;
        };

        class ProcessHelper
        {
        private:
            ProcessHelper();
        public:
            static List<Process*> Processes;
            
            static Process* Create(char* fileName, char* arguments = 0, bool isKernel = false);
            static Process* CreateKernelProcess();
            static void RemoveProcess(Process* proc);
            static void UpdateHeap(Process* proc, common::uint32_t newEndAddr);
            static Process* ProcessById(int id);
        };
    }
}

#endif