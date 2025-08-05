/**
 * @file commands.h
 * @author Ali Mirmohammad
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


#ifndef NOVANIX_KERNEL_COMMANDS_FS_H__
#define NOVANIX_KERNEL_COMMANDS_FS_H__

#include <common/init.hpp>
#include <global.h>

extern INTEGER i_file;

/**
 * ABSTRACT: print all files in dir.
 */
__always_inline VOID print_ls_files_in_dir() {
    BOOL found = false;
    INTEGER file_count = i_file - 1;

    for (INTEGER i = 1; i < file_count; i++) {
        // printk(VGA_WHITE, files[0].name, 1);
        if (String::strcmp(current_directory, files[i].dir)) {
            printk(VGA_WHITE, files[i].name, 1);
            found = true;
            i++;
        }
    }

    if (!found) {
        printk(VGA_WHITE, "No file found in this directory.", 1);
    }
}

#endif /*NOVANIX_KERNEL_COMMANDS_FS_H__*/