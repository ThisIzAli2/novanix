/**
 * @author Ali Mirmohammad
 * @file cactusos.cpp
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
#include <system/syscalls/implementations/Novanix.h>

#include <../../lib/include/syscall.h>
#include <../../lib/include/datetime.h>

#include <system/system.h>
#include <system/tasking/ipcmanager.h>
#include <system/tasking/lock.h>
#include <core/power.h>
#include <system/listings/listingcontroller.h>
#include <system/listings/systeminfo.h>

using namespace Novanix;
using namespace Novanix::common;
using namespace Novanix::core;
using namespace Novanix::system;

MutexLock stdOutStream;
extern PowerRequest powerRequestState; //Defined in kernel.cpp

CPUState* NovanixSyscalls::HandleSyscall(CPUState* state)
{
    Novanix::Systemcalls sysCall = (Novanix::Systemcalls)state->EAX;
    Process* proc = System::scheduler->CurrentProcess();

    switch (sysCall)
    {
        case Novanix::SYSCALL_EXIT:
            Log(Info, "Process %d %s exited with code %d", proc->id, proc->fileName, (int)state->EBX);
            ProcessHelper::RemoveProcess(proc);
            state->EAX = SYSCALL_RET_SUCCES;
            break;
        
        /////////////
        // Logging
        /////////////

        case Novanix::SYSCALL_LOG:
            Log((LogLevel)state->EBX, (const char* __restrict__)state->ECX);
            state->EAX = SYSCALL_RET_SUCCES;
            break;
        case Novanix::SYSCALL_PRINT:
            Print((const char*)state->EBX, state->ECX);
            break;
        
        /////////////
        // VFS
        /////////////
        
        case Novanix::SYSCALL_FILE_EXISTS:
            state->EAX = System::vfs->FileExists((char*)state->EBX);
            break;
        case Novanix::SYSCALL_DIR_EXISTS:
            state->EAX = System::vfs->DirectoryExists((char*)state->EBX);
            break;
        case Novanix::SYSCALL_GET_FILESIZE:
            state->EAX = System::vfs->GetFileSize((char*)state->EBX);
            break;
        case Novanix::SYSCALL_READ_FILE:
            state->EAX = System::vfs->ReadFile((char*)state->EBX, (uint8_t*)state->ECX);
            break;
        case Novanix::SYSCALL_WRITE_FILE:
            state->EAX = System::vfs->WriteFile((char*)state->EBX, (uint8_t*)state->ECX, state->EDX, (bool)state->ESI);
            break;
        case Novanix::SYSCALL_CREATE_FILE:
            state->EAX = System::vfs->CreateFile((char*)state->EBX);
            break;
        case Novanix::SYSCALL_CREATE_DIRECTORY:
            state->EAX = System::vfs->CreateDirectory((char*)state->EBX);
            break;
        case Novanix::SYSCALL_EJECT_DISK:
            state->EAX = System::vfs->EjectDrive((char*)state->EBX);
            break;

        //////////////
        // GUI
        //////////////
        
        case Novanix::SYSCALL_GUI_GETLFB:
            VirtualMemoryManager::mapVirtualToPhysical((void*)System::gfxDevice->framebufferPhys, (void*)state->EBX, pageRoundUp(System::gfxDevice->GetBufferSize()), false, true);
            state->EAX = SYSCALL_RET_SUCCES;
            Log(Info, "Mapped LFB for process %d to virtual address %x", proc->id, state->EBX);
            break;

        case Novanix::SYSCALL_GET_SCREEN_PROPERTIES:
            if(System::gfxDevice) {
                *((int*)state->EBX) = System::gfxDevice->width;
                *((int*)state->ECX) = System::gfxDevice->height;

                state->EAX = SYSCALL_RET_SUCCES;
            }
            else
                state->EAX = SYSCALL_RET_ERROR;
    
            break;
        
        //////////////
        // Memory
        //////////////

        case Novanix::SYSCALL_GET_HEAP_START:
            state->EAX = proc->heap.heapStart;
            break;
        case Novanix::SYSCALL_GET_HEAP_END:
            state->EAX = proc->heap.heapEnd;
            break;
        case Novanix::SYSCALL_SET_HEAP_SIZE:
            ProcessHelper::UpdateHeap(proc, state->EBX);
            state->EAX = SYSCALL_RET_SUCCES;
            break;
        case Novanix::SYSCALL_CREATE_SHARED_MEM:
            {
                Process* proc2 = ProcessHelper::ProcessById(state->EBX);
                if(proc2 == 0) {
                    state->EAX = SYSCALL_RET_ERROR;
                    break;
                }
                state->EAX = SharedMemory::CreateSharedRegion(proc, proc2, state->ECX, state->EDX, state->ESI);
            }
            break;
        case Novanix::SYSCALL_REMOVE_SHARED_MEM:
            {
                Process* proc2 = ProcessHelper::ProcessById(state->EBX);
                if(proc2 == 0) {
                    state->EAX = SYSCALL_RET_ERROR;
                    break;
                }
                state->EAX = SharedMemory::RemoveSharedRegion(proc, proc2, state->ECX, state->EDX, state->ESI);
            }
            break;
        case Novanix::SYSCALL_MAP_SYSINFO:
            {
                //Put systeminfo into address space
                uint32_t sysInfoPhys = (uint32_t)VirtualMemoryManager::virtualToPhysical((void*)System::systemInfo);
                PageTableEntry* sysInfoPage = VirtualMemoryManager::GetPageForAddress(state->EBX, true, true, proc->isUserspace);
                sysInfoPage->readWrite = 1;
                sysInfoPage->isUser = proc->isUserspace;
                sysInfoPage->frame = sysInfoPhys / PAGE_SIZE;
                sysInfoPage->present = 1;

                state->EAX = SYSCALL_RET_SUCCES;
            }
            break;
        
        //////////////
        // Scheduler
        //////////////
        
        case Novanix::SYSCALL_RUN_PROC:
            {    
                char* applicationPath = (char*)state->EBX;
                bool block = (bool)state->ECX;
                if(System::vfs->FileExists(applicationPath) == false) {
                    state->EAX = SYSCALL_RET_ERROR;
                    break;
                }

                Process* newProc = ProcessHelper::Create(applicationPath);
                if(newProc != 0) {
                    if(block) {
                        newProc->Threads[0]->state = Blocked;
                        newProc->Threads[0]->blockedState = Unkown;
                    }
                    else
                        newProc->Threads[0]->state = Started;
                    
                    
                    System::scheduler->AddThread(newProc->Threads[0], false);
                    state->EAX = newProc->id;
                }
                else
                    state->EAX = SYSCALL_RET_ERROR;
            }
            break;
        case Novanix::SYSCALL_SLEEP_MS:
            {
                Thread* currentThread = System::scheduler->CurrentThread();
                currentThread->timeDelta = state->EBX;
                System::scheduler->Block(currentThread, BlockedState::SleepMS);
            }
            break;
        case Novanix::SYSCALL_START_THREAD:
            {     
                Log(Info, "Creating new thread for proc %d %s, jumps to %x", proc->id, proc->fileName, state->EBX);
                //Create new thread
                Thread* newThread = ThreadHelper::CreateFromFunction((void (*)())state->EBX, false, 514, proc);
                
                //Create memory for stack
                for(uint32_t i = (uint32_t)newThread->userStack; i < ((uint32_t)newThread->userStack + newThread->userStackSize); i+=PAGE_SIZE)
                    VirtualMemoryManager::AllocatePage(VirtualMemoryManager::GetPageForAddress(i, true, true, true), false, true);

                //Assign parent
                newThread->parent = proc;
                //Set it as started
                newThread->state = Started;
                //Add it to the parent process
                proc->Threads.push_back(newThread);
                //Add it to the scheduler
                System::scheduler->AddThread(newThread);
                //Force a task switch if the application requested it
                if((bool)state->ECX)
                    System::scheduler->ForceSwitch();
            }
            break;
        case Novanix::SYSCALL_YIELD:
            System::scheduler->ForceSwitch();
            break;
        case Novanix::SYSCALL_PROC_EXIST:
            {
                Process* proc = ProcessHelper::ProcessById(state->EBX);
                if(proc != 0)
                    state->EAX = true;
                else
                    state->EAX = false;
            }
            break;
        case Novanix::SYSCALL_UNBLOCK:
            {
                Process* proc = ProcessHelper::ProcessById(state->EBX);
                if(proc != 0 && (int)state->ECX < proc->Threads.size())
                    proc->Threads[state->ECX]->state = Started;
            }
            break;
        case Novanix::SYSCALL_SET_SCHEDULER:
            {
                bool active = (bool)state->EBX;
                System::scheduler->Enabled = active;
            }
            break;
        case Novanix::SYSCALL_GET_ARGUMENTS:
            {
                char* target = (char*)state->EBX;
                char* src = proc->args;
                if(!src)
                    break;
                
                MemoryOperations::memcpy(target, src, String::strlen(src) <= PROC_ARG_LEN_MAX ? String::strlen(src) : PROC_ARG_LEN_MAX);
            }
            break;

        //////////////
        // IPC
        //////////////
        
        case Novanix::SYSCALL_IPC_SEND:
            IPCManager::HandleSend(state, proc);
            break;
        case Novanix::SYSCALL_IPC_RECEIVE:
            IPCManager::HandleReceive(state, proc);
            break;
        case Novanix::SYSCALL_IPC_AVAILABLE:
            state->EAX = proc->ipcMessages.size();
            break;

        //////////////
        // Clock
        //////////////

        case Novanix::SYSCALL_GET_TICKS:
            {
                uint64_t* ticksPtr = (uint64_t*)state->EBX;
                *ticksPtr = System::pit->Ticks();
                state->EAX = SYSCALL_RET_SUCCES;
            }
            break;
        case Novanix::SYSCALL_GET_DATETIME:
            {
                Novanix::DateTime* resultPtr = (Novanix::DateTime*)state->EBX;
                resultPtr->Day = System::rtc->GetDay();
                resultPtr->Hours = System::rtc->GetHour();
                resultPtr->Minutes = System::rtc->GetMinute();
                resultPtr->Month = System::rtc->GetMonth();
                resultPtr->Seconds = System::rtc->GetSecond();
                resultPtr->Year = System::rtc->GetYear();
                state->EAX = SYSCALL_RET_SUCCES;
            }
            break;
        
        //////////////
        // Power
        //////////////

        case Novanix::SYSCALL_SHUTDOWN:
            Log(Info, "Process requested shutdown");
            powerRequestState = Shutdown; //Tell kernel process to shutdown on next schedule
            
            state->EAX = SYSCALL_RET_SUCCES;
            break;
        case Novanix::SYSCALL_REBOOT:
            Log(Info, "Process requested reboot");
            powerRequestState = Reboot; //Tell kernel process to reboot on next schedule

            state->EAX = SYSCALL_RET_SUCCES;
            break;
        
        //////////////
        // STDIO
        //////////////        

        case Novanix::SYSCALL_READ_STDIO:
            if(proc->stdInput != 0)
            {
                while (proc->stdInput->Available() <= 0) //TODO: Use blocking here
                    System::scheduler->ForceSwitch();
                state->EAX = proc->stdInput->Read();
            }
            else
                Log(Warning, "StdIn is zero for process %s", proc->fileName);

            break;
        case Novanix::SYSCALL_WRITE_STDIO:
            if(proc->stdOutput != 0) {
                char* data = (char*)state->EBX;
                if(data == 0 || state->ECX <= 0)
                    break;
                
                //This makes sure output text does not get mixed up when interrupted during writing.
                if(proc->stdOutput == System::ProcStandardOut)
                    stdOutStream.Lock();

                for(uint32_t d = 0; d < state->ECX; d++)
                    proc->stdOutput->Write(data[d]);

                //Don't forget to unlock
                if(proc->stdOutput == System::ProcStandardOut)
                    stdOutStream.Unlock();
            }
            else
                Log(Warning, "StdOut is zero for process %s", proc->fileName);
            
            break;
        case Novanix::SYSCALL_REDIRECT_STDIO:
            {
                int fromID = state->EBX;
                int toID = state->ECX;

                if(fromID == -1) //Redirect to keyboard
                {
                    Process* toProc = ProcessHelper::ProcessById(toID);
                    
                    Log(Info, "Redirecting keyboard stream to StdIn of %s", toProc->fileName);
                    toProc->stdInput = System::keyboardManager;
                    break;
                }

                Process* fromProc = ProcessHelper::ProcessById(fromID);
                Process* toProc = ProcessHelper::ProcessById(toID);
                if(fromProc == 0 || toProc == 0)
                    break;

                Log(Info, "Redirecting StdOut from %s to StdIn of %s", fromProc->fileName, toProc->fileName);

                if(toProc->stdInput == System::keyboardManager || toProc->stdInput == 0)
                    toProc->stdInput = new FIFOStream();
                
                fromProc->stdOutput = toProc->stdInput;
            }
            break;
        case Novanix::SYSCALL_STDIO_AVAILABLE:
            if(proc->stdInput != 0)
                state->EAX = proc->stdInput->Available();
            else
                state->EAX = 0;
            
            break;

        //////////////
        // Listings
        //////////////        

        case Novanix::SYSCALL_BEGIN_LISTING:
            {
                int type = state->EBX;
                if(!(System::listings->size() > type)) {
                    state->EAX = 0;
                    break;
                }
                    
                state->EAX = System::listings->GetAt(type)->BeginListing(System::scheduler->CurrentThread(), state->ECX);
            }
            break;
        case Novanix::SYSCALL_LISTING_ENTRY:
            {
                int type = state->EBX;
                if(!(System::listings->size() > type)) {
                    state->EAX = 0;
                    break;
                }

                state->EAX = System::listings->GetAt(type)->GetEntry(System::scheduler->CurrentThread(), (int)state->ECX, state->EDX);
            }
            break;
        case Novanix::SYSCALL_END_LISTING:
            {
                int type = state->EBX;
                if(!(System::listings->size() > type)) {
                    state->EAX = 0;
                    break;
                }

                System::listings->GetAt(type)->EndListing(System::scheduler->CurrentThread());
            }
            break;
        case Novanix::SYSCALL_GET_SYSINFO_VALUE:
            {
                state->EAX = SystemInfoManager::HandleSysinfoRequest((void*)state->EBX, state->EDX, state->ECX, (bool)state->ESI);
            }
            break;
        default:
            Log(Warning, "Got unkown syscall %d from process %d", sysCall, proc->id);
            state->EAX = SYSCALL_RET_ERROR;
            break;
    }

    return state;
}