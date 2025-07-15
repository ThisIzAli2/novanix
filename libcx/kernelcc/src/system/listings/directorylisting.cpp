/**
 * @author Ali Mirmohammad
 * @file directorylisting.cpp
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
#include <system/listings/directorylisting.h>
#include <system/system.h>
#include <typing.hpp>

using namespace Novanix;
using namespace Novanix::common;
using namespace Novanix::core;
using namespace Novanix::system;

// List which holds the files in the current requested directory.
List<Novanix::VFSEntry>* currentDirectoryList = 0;

DirectoryListing::DirectoryListing()
: ListingController() { }

INTEGER DirectoryListing::BeginListing(Thread* thread, uint32_t pathPtr)
{
    char* path = (char*)pathPtr;
    if(!System::vfs->DirectoryExists(path))
        return -1;
    
    if(requestBusy)
    {
        waitingQueue.push_back(thread);
        System::scheduler->Block(thread);
    }

    requestBusy = true;
    currentReqThread = thread;

    currentDirectoryList = System::vfs->DirectoryList(path);
    return currentDirectoryList->size();
}
INTEGER DirectoryListing::GetEntry(Thread* thread, INTEGER entry, uint32_t bufPtr)
{
    char* buf = (char*)bufPtr;
    if(currentReqThread != thread)
    {
        Log(Error, "Thread requested entry while it was not the original requestor");
        return 0;
    }

    if(entry >= 0 && currentDirectoryList->size() > entry && buf != 0)
    {
        Novanix::VFSEntry item = currentDirectoryList->GetAt(entry);
        MemoryOperations::memcpy(buf, &item, sizeof(Novanix::VFSEntry));

        return 1;
    }
    
    // End of items
    return 0;
}
VOID DirectoryListing::EndListing(Thread* thread)
{
    if(currentReqThread != thread || currentReqThread == 0)
    {
        Log(Error, "Thread requested listing end while it was not the original requestor");
        return;
    }

    requestBusy = false;
    currentReqThread = 0;
    delete currentDirectoryList;

    if(waitingQueue.size() > 0) //Unblock first thread from queue.
        System::scheduler->Unblock(waitingQueue[0]);
}