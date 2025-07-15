/**
 * @author Ali Mirmohammad
 * @file ipcmanager.cpp
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
#include <../../lib/include/syscall.h>
#include <system/tasking/ipcmanager.h>
#include <system/system.h>
#include <typing.hpp>

using namespace Novanix;
using namespace Novanix::common;
using namespace Novanix::core;
using namespace Novanix::system;

List<IPCReceiveDescriptor>* receivingBlockedList;
VOID IPCManager::Initialize()
{
    receivingBlockedList = new List<IPCReceiveDescriptor>();
}

//Called from systemcalls when process tries to send a ipc message
VOID IPCManager::HandleSend(core::CPUState* state, Process* proc)
{
    //Log(Info, "IPC Send from process %s", proc->fileName);
    // Get message pointer from ebx register
    Novanix::IPCMessage* msg = (Novanix::IPCMessage*)state->EBX;
    
    //Check if the source is valid
    if (msg->source != proc->id) {
        state->EAX = SYSCALL_RET_ERROR;
        return;
    }

    // To which process is this message meant to be send to
    Process* target = ProcessHelper::ProcessById(msg->dest);
    if (target == 0) {
        state->EAX = SYSCALL_RET_ERROR;
        return;
    }

    //Add the message to the buffer of the target process
    target->ipcMessages.push_back(*msg);

    INTEGER i = 0;
    for(IPCReceiveDescriptor desc : *receivingBlockedList) {
        if(desc.receivingProcess == target && (desc.receiveFromPID == -1 ? true : desc.receiveFromPID == proc->id) && (desc.receiveType == -1 ? true : desc.receiveType == msg->type))
        {    
            Thread* receivingThread = desc.receivingThread;
            if(receivingThread == 0)
                continue;
            
            receivingBlockedList->Remove(i);
            System::scheduler->Unblock(receivingThread);
            break;
        }
        i++;
    }

    state->EAX = SYSCALL_RET_SUCCES;
}

//ebx = Message pointer
//Called from systemcalls when process tries to receive a ipc message
VOID IPCManager::HandleReceive(core::CPUState* state, Process* proc)
{
    //Log(Info, "IPC Receive from process %s", proc->fileName);
    INTEGER recvFrom = state->ECX;
    INTEGER* errRet = (INTEGER*)state->EDX;
    INTEGER type = state->ESI;

    //We need to block ourself if there are no messages at the moment
    if (proc->ipcMessages.size() <= 0) {
        //Generate IPC Receive Descriptor
        IPCReceiveDescriptor desc;

        //////////
        // Fill in variables
        //////////
        desc.receivingProcess = proc;
        desc.receivingThread = System::scheduler->CurrentThread();
        desc.receiveFromPID = recvFrom;
        desc.receiveType = type;

        //Add this thread to the list of blocked processes
        receivingBlockedList->push_back(desc);
        System::scheduler->Block(desc.receivingThread, BlockedState::ReceiveIPC);
    }

    //If we get here we are either unblocked or there was already a message ready to receive
    INTEGER messageIndex = 0;
    Novanix::IPCMessage message = proc->ipcMessages.GetAt(messageIndex);
    
    //Loop throug all the messages until we find a correct one.
    while ((message.dest != proc->id || (recvFrom == -1 ? false : recvFrom != message.source) || (type == -1 ? false : type != message.type)) && (messageIndex < proc->ipcMessages.size())) { //Is the message not for us or not from the correct source
        proc->ipcMessages.GetAt(++messageIndex);
    }

    //We did not find a message that is for us or has the right parameters
    if(messageIndex == proc->ipcMessages.size())
    {
        if (errRet != 0)
            *errRet = SYSCALL_RET_ERROR;
        return;
    }

    //Copy message
    Novanix::IPCMessage* targetMessage = (Novanix::IPCMessage*)state->EBX;
    MemoryOperations::memcpy(targetMessage, &message, sizeof(Novanix::IPCMessage));

    //Remove it from the list
    proc->ipcMessages.Remove(messageIndex);

    if (errRet != 0)
        *errRet = SYSCALL_RET_SUCCES;
}