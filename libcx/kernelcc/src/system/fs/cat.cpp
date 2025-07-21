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


VOID cat_file(char* file) {
    for (INTEGER i = 0; i < MAX_FILES; i++) {
        if (files[i].name == nullptr) continue; // skip empty entries, This is important

        if (String::strcmp(files[i].name, file) == 0) {
            printk(VGA_WHITE, files[i].data, 1);
            return;
        }
    }

    printk(VGA_WHITE, "File not found", 1);
}
