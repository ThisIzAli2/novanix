#ifndef __NOVA_KERNEL_FILE_H
#define __NOVA_KERNEL_FILE_H

#define MAX_FILES 8
#define MAX_FILE_SIZE 4096
#define MAX_FILENAME_LEN 64



typedef struct {
    char name[MAX_FILENAME_LEN];
    char content[MAX_FILE_SIZE];
    int size;
    int cursor;
    int used;
} File;





#endif // __NOVA_KERNEL_FILE_H