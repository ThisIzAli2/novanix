/**
 * @author Ali Mirmohammad
 * @file contextmanager.cpp
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
#include "contextmanager.h"

using namespace Novanix;

ContextManager::ContextManager()
: contextList()
{ }

ContextManager::~ContextManager()
{ }

ContextInfo* ContextManager::FindTargetContext(int x, int y)
{
    // Loop through all known contexts starting at the one on the front
    for(ContextInfo* c : contextList)
    {
        if(x >= c->x && x <= c->x + (int)c->width)       // Check if the coordinate x,y fits in the border
            if(y >= c->y && y <= c->y + (int)c->height)  // of the context. If so return as result.
                return c;
    }

    return 0;
}
List<ContextInfo*> ContextManager::FindTargetContexts(Rectangle area)
{
    List<ContextInfo*> result;
    for(ContextInfo* c : contextList)
    {
        Rectangle item = Rectangle(c->width, c->height, c->x, c->y);
        if(area.Intersect(item, 0))
            result.push_back(c);
    }
    return result;
}

void ContextManager::MoveToFront(ContextInfo* info)
{
    contextList.Remove(info);
    contextList.push_front(info);
}