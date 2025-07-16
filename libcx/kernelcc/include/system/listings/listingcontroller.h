/**
 * @author Ali Mirmohammad
 * @file listingcontroller.h
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
#ifndef __Novanix__SYSTEM__VFS__LISTINGCONTROLLER_H
#define __Novanix__SYSTEM__VFS__LISTINGCONTROLLER_H

#include <system/vfs/virtualfilesystem.h>
#include <system/tasking/process.h>

namespace Novanix
{
    namespace system
    {
        // A class that creates an easy interface for threads to request a list from the kernel.
        // This can for example be a list of files or processes.
        class ListingController
        {
        protected:
            // Threads that have also requested a listing before an other one was finished.
            List<Thread*> waitingQueue;
            
            // Current thread which has requested a list
            Thread* currentReqThread;

            // Are we currently handling a request?
            bool requestBusy = false;
        public:
            ListingController();

            virtual int BeginListing(Thread* thread, uint32_t arg1 = 0);
            virtual int GetEntry(Thread* thread, int entry, uint32_t bufPtr);
            virtual void EndListing(Thread* thread);
        };
    }
}

#endif