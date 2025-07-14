/**
 * @author Ali Mirmohammad
 * @file fcreate.cpp
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


#include <software/fcreate.h>
#include <software/help/ops.h>
#include <fs/fs.h>
#include <software/edit.h>

using namespace Novanix::common;
using namespace Novanix::system;

file_t __create_file(char* name,char* data,int size){
    file_t file;
    static char binary_output[1024];
    if (size > 0){
        MemoryOperations::memset(name,string_to_binary(data),size);
        file.name = name;
        file.data = data;
        file.size = size;
    }
    printk(VGA_COLOR_WHITE,"File created!",1);
    return file;
}

void create_file_function(){
    char* data = draw_editor();
    __create_file("name.txt",data,sizeof(data));
}