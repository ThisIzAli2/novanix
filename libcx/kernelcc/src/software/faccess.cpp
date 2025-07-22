/**
 * @author Ali Mirmohammad
 * @file faccess.cpp
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
#include <software/faccess.h>
#include <software/fcreate.h>
#include <common/init.hpp>

using namespace Novanix::common;

file_t* find_file_by_name(file_t* files, INTEGER file_count, const char* target_name) {
    for (int i = 0; i < file_count; i++) {
        if (String::strcmp(files[i].name, target_name) == 0) {
            return &files[i];
        }
    }
    return nullptr;  // Not found
}

void read_file(char* file_name){
    if (find_file_by_name(files,COUNT_FILES(files),file_name) == nullptr){
        printk(VGA_COLOR_RED,"Does not exist",1);
    } else{
        printk(VGA_COLOR_WHITE,"Does exist",1);
    }
}

