#ifndef __NOVANIX_FILE_HANDLE_H
#define __NOVANIX_FILE_HANDLE_H

#include <common/init.hpp>

#define FILE_NAME_MAX 15

__always_inline VOID create_file(const char name[FILE_NAME_MAX]){
    int len = 0;
    while(len < FILE_NAME_MAX && name[len] != '\0'){
        len++;
    }
    if (len == FILE_NAME_MAX && name[FILE_NAME_MAX - 1] != '\0'){
        Novanix::system::printk(Novanix::system::VGA_COLOR_RED,"Error",1);
    } else{
        Novanix::system::printk(Novanix::system::VGA_COLOR_GREEN,"Your file has been created",1);
    }
}


#endif // __NOVANIX_FILE_HANDLE_H