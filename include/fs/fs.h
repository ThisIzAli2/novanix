#ifndef __NOVANIX_KERNEL_FS_H
#define __NOVANIX_KERNEL_FS_H


#include <common/init.hpp>


typedef struct File{
    char* name;
    char* data;
    int size;
} file_t;



#endif /*__NOVANIX_KERNEL_FS_H*/