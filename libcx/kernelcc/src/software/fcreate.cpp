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
#include <global.h>
#include <software/edit.h>
#include <system/memory/heap.h>


using namespace Novanix::common;
using namespace Novanix::system;

static uint32_t seed = 1;



/**
 * @brief A function that creates a file for the system
 */
file_t __create_file(char* name, char* data, INTEGER size, bool access_req) {
    uint32_t dummy = 0;
    file_t result = {0}; // zero-init

    if (size <= 0) {
        printk(VGA_COLOR_RED, "Error: File creation failed (invalid size).", 1);
        return result;
    }
    if (i_file >= MAX_FILES) {
        printk(VGA_COLOR_RED, "Error: File creation failed (max files reached).", 1);
        return result;
    }

    // Declare all at top
    char* name_copy = nullptr;
    char* data_copy = nullptr;
    char* dir_copy  = nullptr;
    size_t name_len = 0;
    size_t dir_len  = 0;

    // Allocate name
    name_len = String::strlen(name);
    name_copy = (char*) KernelHeap::malloc(name_len + 1, &dummy);
    if (!name_copy) goto oom;
    String::strcpy(name_copy, name);

    // Allocate data
    data_copy = (char*) KernelHeap::malloc(size + 1, &dummy);
    if (!data_copy) goto oom;
    MemoryOperations::memcpy(data_copy, data, size);
    data_copy[size] = '\0';

    // Allocate dir
    dir_len = String::strlen(current_directory);
    dir_copy = (char*) KernelHeap::malloc(dir_len + 1, &dummy);
    if (!dir_copy) goto oom;
    String::strcpy(dir_copy, current_directory);

    // Store in files[]
    files[i_file].name   = name_copy;
    files[i_file].data   = data_copy;
    files[i_file].dir    = dir_copy;
    files[i_file].size   = size;
    files[i_file].access = access_req;

    // Copy into return struct
    result = files[i_file];

    // Debug
    printk(VGA_COLOR_WHITE, "File created!", 1);
    printk(VGA_COLOR_WHITE, "File name: ", 0);
    printk(VGA_COLOR_WHITE, files[i_file].name, 1);
    printk(VGA_COLOR_WHITE, "File size (bytes): ", 0);
    printk(VGA_COLOR_WHITE, stringify(files[i_file].size), 1);
    printk(VGA_COLOR_WHITE, "In the directory: ", 0);
    printk(VGA_COLOR_WHITE, files[i_file].dir, 1);

    i_file++;
    file_c++;
    return result;

oom:
    if (name_copy) KernelHeap::free(name_copy);
    if (data_copy) KernelHeap::free(data_copy);
    if (dir_copy)  KernelHeap::free(dir_copy);
    printk(VGA_COLOR_RED, "Error: Memory allocation failed during file creation.", 1);
    return result;
}


static inline uint32_t rand_next() {
    seed = (1103515245 * seed + 12345) & 0x7fffffff;
    return seed;
}

// Always generate exactly 4-character random string
char* generate_random_string() {
    static char buffer[5]; // 4 chars + null terminator
    static const char charset[] =
        "abcdefghijklmnopqrstuvwxyz"
        "0123456789";
    
    uint32_t charset_size = sizeof(charset) - 1;

    for (uint32_t i = 0; i < 4; i++) {
        buffer[i] = charset[rand_next() % charset_size];
    }

    buffer[4] = '\0';
    return buffer;
}

/**
 * @brief a function that creates a file, gives the data as an input.
 */
VOID create_file_function(char* data,char* name){
    file_t file = __create_file(name,data,String::strlen(data)+1,false);
    files[i_file++].data = file.data;
}

file_t __create_empty_file(char* name){
    file_t file;

    file.name = name;
    file.data = "";
    file.size = DEFAULT_FILE_SIZE; 
    return file;
}


/**
 * @brief This function is used for the "touch" command.
 * NOTE: This method is unsafe now!
 */
VOID create_empty_file(char* name){
    file_t file = __create_empty_file(name);
    files[i_file].name = file.name;
    files[i_file].data = file.data;
    files[i_file].size = file.size;
    
}