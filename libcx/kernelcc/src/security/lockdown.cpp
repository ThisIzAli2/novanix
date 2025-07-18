/**
 * @file lockdown.cpp
 * @author Ali Mirmohammad
 * 
 ** This file is part of Novanix.

**AliNix is free software: you can redistribute it and/or modify
**it under the terms of the GNU Affero General Public License as published by
**the Free Software Foundation, either version 3 of the License, or
**(at your option) any later version.

**AliNix is distributed in the hope that it will be useful,
**but WITHOUT ANY WARRANTY; without even the implied warranty of
**MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
**GNU Affero General Public License for more details.

**You should have received a copy of the GNU Affero General Public License
**along with AliNix. If not, see <https://www.gnu.org/licenses/>.
*/
#include <security/lockdown.h>

/**
 * @brief Put the system into the lockdown.
 */
VOID put_system_lockdown(enum LOCKDOWN_REASON reason){
    switch (reason){
        case ROOT_ACCESS_FAILED:
            printk(VGA_COLOR_RED,"You have tried too many wrong passwords for the sudo access. The kernel is going to be put in the lockdown. Please restart your system, if you believe this is a mistake.",1);
            HALT_COMMAND;
    }
}