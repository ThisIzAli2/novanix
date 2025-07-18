/**
 * @author Ali Mirmohammad
 * @file memaccess.cpp
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
#include <security/memaccess.h>
#include <access.h>


/**
 * Reset the super user access, if there was a try to access and destroy the memory.
 */
VOID reset_super_access(){
    if (have_access){
        have_access = false;
    } else{
        return;
    }
}