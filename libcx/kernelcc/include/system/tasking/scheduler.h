/**
 * @author Ali Mirmohammad
 * @file scheduler.h
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
#ifndef __Novanix__SYSTEM__TASKING__SCHEDULER_H
#define __Novanix__SYSTEM__TASKING__SCHEDULER_H

#include <common/types.h>
#include <system/interruptmanager.h>
#include <system/tasking/thread.h>

namespace Novanix
{
    namespace system
    {
        #define SCHEDULER_FREQUENCY 30

        class Scheduler : public InterruptHandler
        {
        private:
            common::uint32_t frequency = 0;
            common::uint32_t tickCount = 0;

            List<Thread*> threadsList;
            Thread* currentThread = 0;

            Thread* GetNextReadyThread();
            void ProcessSleepingThreads();

            bool switchForced = false; //Is the current switch forced by a forceSwitch() call?
        public:
            bool Enabled = true;
            Scheduler();

            common::uint32_t HandleInterrupt(common::uint32_t esp);

            void AddThread(Thread* thread, bool forceSwitch = false);
            void ForceSwitch();

            Thread* CurrentThread();
            Process* CurrentProcess();

            void InitialThreadUserJump(Thread* thread);

            //Blocking and unblocking
            void Block(Thread* thread, BlockedState reason = BlockedState::Unkown);
            void Unblock(Thread* thread, bool forceSwitch = false);
        };
    }   
}

#endif