#ifndef __NOVANIX_KERNEL_FILE_SYSTEM_H_NEW_
#define __NOVANIX_KERNEL_FILE_SYSTEM_H_NEW_


#include <common/string.h>
#include <system/log.h>
#include <system/bootconsole.h>

using namespace Novanix::system;



#define CURRENT_DIR_BUFFER_SIZE 256



class FileSystem{
    private:
     char currentDirectory[CURRENT_DIR_BUFFER_SIZE];
    struct Directory {
        const char* name;
        Directory* subdirectories;
        int subdirectoryCount;
    } root;

    Directory* findDirectory(Directory* dir,const char* name){
        for (int i = 0;i < dir->subdirectoryCount;i++){
            if (Novanix::common::String::strcmp(dir->subdirectories[i].name, name)){
                    return &dir->subdirectories[i];

            }
        }
        return nullptr;
    } 
    
    
};

#endif