/**
 * @author Ali Mirmohammad
 * @file debugger.h
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
#ifndef __DEBUGGER_H
#define __DEBUGGER_H

#include "compositor.h"

class Compositor;

// Class used to display usefull debugging information when testing the compositor
class CompositorDebugger
{
private:
    // To which compositor is this debugger atached?
    Compositor* target = 0;
public:
    // Is the debugger enabled?
    bool enabled = false;

    // Create a new instance of a CompositorDebugger
    CompositorDebugger(Compositor* target);


    // Handle the debugging of one specific context
    // Called for every context every frame
    void ProcessContext(ContextInfo* ctx);

    // Handles any additional debugging for each frame
    void ProcessGeneral();
};

#endif