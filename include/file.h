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

int open(const char* filename, int flags);
int read(int fd, char* buf, int size);
int write(int fd, const char* buf, int size);
int close(int fd);
void init_filesystem();

#define O_RDONLY 0x01
#define O_WRONLY 0x02
#define O_CREAT  0x04




#endif // __NOVA_KERNEL_FILE_H