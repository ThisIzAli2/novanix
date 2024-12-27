#ifndef __NOVANIX_KERNEL_FILE_SYSTEM_H_NEW_
#define __NOVANIX_KERNEL_FILE_SYSTEM_H_NEW_


#include <common/string.h>


#define CURRENT_DIR_BUFFER_SIZE 256

class FileSystem{
    private:
        char current_dir [CURRENT_DIR_BUFFER_SIZE];
        struct Directory {
        const char* name;
        Directory* subdirectories;
        int subdirectoryCount;
    } root;
};

#endif
