#ifndef __LIST_FILES
#define __LIST_FILES



#include <typing.hpp>
#include <types.h>
#include <common/init.hpp>


VOID create_file(const char* file_name,INTEGER size){
    if (!file_name || !size){
        Novanix::system::printk(VGA_COLOR_WHITE,"ERROR!",1);
    }
    else{
        Novanix::system::printk(VGA_COLOR_WHITE,"Creating file: ",1);
    }
}




#endif /*__LIST_FILES*/