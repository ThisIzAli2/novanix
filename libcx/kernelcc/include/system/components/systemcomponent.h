/**
 * @author Ali Mirmohammad
 * @file systemcomponents.h
 * @Credits Remco123
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
#ifndef __Novanix__SYSTEM__COMPONENTS_H
#define __Novanix__SYSTEM__COMPONENTS_H

#include <common/types.h>

namespace Novanix
{
    namespace system
    {
        class SystemComponent
        {
        private:
            char* Name;
            char* Description;
        public:
            SystemComponent(char* name = 0, char* description = 0);

            char* GetComponentName();
            char* GetComponentDescription();
        };
    }
}

#endif