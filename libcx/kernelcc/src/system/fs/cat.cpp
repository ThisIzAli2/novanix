/**
 * @author Ali Mirmohammad
 * @file cat.cpp
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
#include <fs/cat.h>
#include <system/memory/heap.h>

using namespace Novanix::system;

/**
 * @brief Used to utilize 'cat' command.
 * NOTE: Do not use == 0 in String::strcmp(files[i].name, file)
 */
VOID cat_file(char* file) {
    
    for (INTEGER i = 0; i < MAX_FILES; i++) {
        if (!have_access && files[i].access){
            printk(VGA_RED,"You do not have access to this file",1);
            return;
        }
        // if (files[i].name == nullptr) continue; //! Do not use this. This will ignore spaces.
        if (String::strcmp(files[i].name, file)) {
            printk(VGA_WHITE, files[i].data, 1);
            return;
        } else{
            printk(VGA_WHITE,"file not found",1);
        }
    }

}
