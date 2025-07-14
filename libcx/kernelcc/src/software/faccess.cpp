#include <software/faccess.h>
#include <software/fcreate.h>
#include <common/init.hpp>

using namespace Novanix::common;

file_t* find_file_by_name(file_t* files, int file_count, const char* target_name) {
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

