/**
 * @author Ali Mirmohammad
 * @file main.cpp
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
#include <new.h>
#include <log.h>
#include <time.h>
#include <proc.h>
#include <gui/directgui.h>

#include "compositor.h"

using namespace Novanix;

int main(int argc, char** argv)
{
    Compositor* mainCompositor = new Compositor();
    while(1) 
    {
        // Update cursor position with the value stored in SysInfo
        mainCompositor->curMouseX = Process::systemInfo->MouseX;
        mainCompositor->curMouseY = Process::systemInfo->MouseY;
        mainCompositor->curMouseZ = Process::systemInfo->MouseZ;

        ///////////////////////////
        // Process GUI Events
        ///////////////////////////
        mainCompositor->ProcessEvents();

        ///////////////////////////
        // Process GUI Requests from clients
        ///////////////////////////
        mainCompositor->ProcessRequests();

        ///////////////////////////
        // Draw a new version of the desktop
        ///////////////////////////
        mainCompositor->DrawFrame();

        // Update cursor variables for next run
        mainCompositor->prevMouseX = mainCompositor->curMouseX;
        mainCompositor->prevMouseY = mainCompositor->curMouseY;
        mainCompositor->prevMouseZ = mainCompositor->curMouseZ;

        // Switch processes after drawing desktop
        // It is useless to draw it like 30 times in a couple milliseconds.
        Process::Yield();
    }

    delete mainCompositor;
    return 0;
}