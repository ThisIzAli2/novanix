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

static uint32_t seed = 123456789;
char buffer[16 + 1];

uint32_t inline rand_next() {
    seed = (1103515245 * seed + 12345) & 0x7fffffff;
    return seed;
}

// Generates a random string of length `len`
// `out` must point to a buffer at least `len+1` bytes large
void inline generate_random_string(char* out, uint32_t len) {
    static const char charset[] =
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz"
        "0123456789";

    uint32_t charset_size = sizeof(charset) - 1;

    for (uint32_t i = 0; i < len; i++) {
        uint32_t rand_val = rand_next();
        out[i] = charset[rand_val % charset_size];
    }
    out[len] = '\0'; // Null-terminate
    
}

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
    printk(VGA_COLOR_WHITE,file.name,1);
    printk(VGA_COLOR_WHITE,file.data,1);
    printk(VGA_COLOR_WHITE,stringify(file.size),1);
    return file;
}

char* generate_random_string(uint32_t len) {
    static char buffer[256]; // max length 255 chars + null terminator
    if (len >= sizeof(buffer)) {
        len = sizeof(buffer) - 1;
    }

    static const char charset[] =
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz"
        "0123456789";

    uint32_t charset_size = sizeof(charset) - 1;

    for (uint32_t i = 0; i < len; i++) {
        uint32_t rand_val = rand_next();
        buffer[i] = charset[rand_val % charset_size];
    }
    buffer[len] = '\0';
    return buffer;
}

void create_file_function(char* data){
    __create_file(generate_random_string(4),data,sizeof(data));
}