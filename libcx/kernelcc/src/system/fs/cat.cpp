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

#define DEV_CAT

#undef DEV_CAT

/**
 * @brief Used to utilize 'cat' command.
 * NOTE: Do not use == 0 in String::strcmp(files[i].name, file)
 */
VOID cat_file(char* file) {
    size_t size = sizeof(files) / sizeof(files[0]);
    #if defined(DEV_CAT)
    printk(VGA_WHITE,stringify(size),1);
    #endif

    INTEGER i;
    for (i = 0; i < i_file; i++) {
        #if defined(DEV_CAT)
        printk(VGA_WHITE,stringify(i_file),1);
        #endif
        //! Make sure to check for the null pointer, it can lead to crash.
        // if (files[i].name == nullptr) continue; //! Do not use this. This will empty ignore spaces.
        if (files[i].name != nullptr && file != nullptr && String::strcmp(files[i].name, file)) {
            printk(VGA_WHITE, files[i_file].data, 1);
            return;
        } else{
            // This part is crucial, you should always write 'continue' to continue searching
            continue;
        }
    }
    printk(VGA_WHITE,"file not found",1);

}
