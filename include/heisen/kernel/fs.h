#ifndef _HEISEN_FILE_SYSTEM_KERNEL_INCLUDE_H
#define _HEISEN_FILE_SYSTEM_KERNEL_INCLUDE_H

#include <heisen/typing.h>

#define BLOCK_SIZE 512
#define SFS_TYPE_ID 0x05F50010

#define ROOT_PATH_DIR "."
#define PATH_SEPARATOR   '/'
#define PATH_SEPARATOR_S "/"


typedef struct sfs_superblock_t{
    uint32_t fType;
    uint32_t fSize;
    uint32_t fNentries;
    uint32_t fBootStart;
}sfs_superblock_t;


#define T_DIR 0x01
#define T_FILE 0x02

#define SFS_NAMESIZE    15  // Max length of entry name + final 0
#define SFS_ENTRYREFS  120  // Number of references in a single entry


#define F_USED (T_DIR | T_FILE)



typedef struct sfs_entry_t{
    uint8_t flag;
    uint8_t name[SFS_NAMESIZE];
    uint32_t time;
    uint32_t  size;               // File size (bytes) or number of items in a dir
    uint32_t  parent;             // Parent dir entry, or previous chained entry
    uint32_t  next;               // Next chained entry index. See below
    uint32_t  ref[SFS_ENTRYREFS]; // References to blocks or entries. See below
}sfs_entry_t;


#ifndef MKFS

    void fs_init_info();
    uint fs_get_info(uint disk, fs_info_t *info);
    uint fs_get_entry(sfs_entry_t *entry, char *path, uint parent, uint disk);

// Read file
// Output: buff
// Reads count bytes of path file starting at byte offset inside this file.
// Returns number of readed bytes or ERROR_NOT_FOUND
uint fs_read_file(void *buff, char *path, uint offset, size_t count);

// Write file flags
#define WF_CREATE   0x0001 // Create file if it does not exist
#define WF_TRUNCATE 0x0002 // Truncate file to the last written position

// Write file
// Writes count bytes of path file starting at byte offset inside this file.
// If target file is not big enough, its size is increased.
// Depending on flags, path file can be created or truncated.
// Returns number of written bytes or ERROR_NOT_FOUND
uint fs_write_file(const void *buff, char *path, uint offset, size_t count, uint flags);

// Move entry
// In the case of directories, they are recursively moved
// Returns:
// - ERROR_NOT_FOUND if source does not exist
// - ERROR_EXISTS if destination exists
// - another value otherwise
uint fs_move(char *srcpath, char *dstpath);

// Copy entry
// In the case of directories, they are recursively copied
// Returns:
// - ERROR_NOT_FOUND if source does not exist
// - ERROR_EXISTS if destination exists
// - another value otherwise
uint fs_copy(char *srcpath, char *dstpath);

// Delete entry
// In the case of directories, they are recursively deleted
// Returns:
// - ERROR_NOT_FOUND if path does not exist
// - index of deleted entry otherwise
uint fs_delete(char *path);

// Create a directory
// Returns:
// - ERROR_NOT_FOUND if parent path does not exist
// - ERROR_EXISTS if destination already exists
// - index of created entry otherwise
uint fs_create_directory(char *path);

// List directory entries
// Output: entry
// Gets entry with index n in path directory
// Returns:
// - ERROR_NOT_FOUND if path does not exist
// - number of elements in ths directory otherwise
uint fs_list(sfs_entry_t *entry, char *path, uint n);

// Create filesystem in disk
// Deletes all files, creates NSFS filesystem
// and adds a copy of the kernel
// Returns NO_ERROR on success
uint fs_format(uint disk);

// Convert fs time to system time_t
// See fs time format specification above
uint fs_fstime_to_systime(uint32_t fst, time_t *syst);

// Convert system time_t to fs time
// See fs time format specification above
uint32_t fs_systime_to_fstime(time_t *syst);

// Auxiliar functions
const char *disk_to_string(uint disk);
uint string_to_disk(const char *str);
uint blocks_to_MB(uint blocks);

// Debug functions
uint fs_print_map(char *filename);

#endif 


#endif // _HEISEN_FILE_SYSTEM_KERNEL_INCLUDE_H