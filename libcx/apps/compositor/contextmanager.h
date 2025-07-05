/**
 * @author Ali Mirmohammad
 * @file contextmanager.h
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
#ifndef __CONTEXTMANAGER_H
#define __CONTEXTMANAGER_H

#include <types.h>
#include <list.h>
#include <gui/contextinfo.h>

// Class that manages a list of contexts
class ContextManager
{
private:

public:
    // List of al contexts present on the desktop
    // Organized from top to bottom, so top context is at position 0
    List<ContextInfo*> contextList;

    // Initialize a new instance of the ContextManager
    ContextManager();

    // Destructor
    ~ContextManager();

    
    // Find the corresponding context at the position given by x and y
    // The order is from top to bottom!
    ContextInfo* FindTargetContext(int x, int y);

    // Find all contexts that exist in the given area
    List<ContextInfo*> FindTargetContexts(Rectangle area);

    // Move a context to the front of the desktop
    void MoveToFront(ContextInfo* info);
};

#endif