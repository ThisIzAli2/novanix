/**
 * @author Ali Mirmohammad
 * @file ipcmanager.h
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
#ifndef __Novanix__SYSTEM__TASKING__IPCMANAGER_H
#define __Novanix__SYSTEM__TASKING__IPCMANAGER_H

#include <core/registers.h>
#include <system/tasking/process.h>

namespace Novanix
{
    namespace system
    {
        struct IPCReceiveDescriptor
        {
            // Which process is waiting for a message?
            Process* receivingProcess;
            // Which thread called receive and is currently blocked.
            Thread* receivingThread;
            // Do we need to receive the message from a specific process?
            int receiveFromPID;
            // Do we need to receive a specific type of message?
            int receiveType;
        };

        class IPCManager
        {
        public:
            static void Initialize();
            static void HandleSend(core::CPUState* state, Process* proc);
            static void HandleReceive(core::CPUState* state, Process* proc);
        };
    }
}

#endif