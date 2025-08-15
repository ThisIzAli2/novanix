#include <fs/hfs/hfs.h>
#include <fs/diskio.h>

VOID hfs_read_block(uint32_t blockNum, uint8_t* buffer) {
    disk_read(blockNum,buffer,512);
}