#include <fs/ntfs/ntfs.h>

void ntfs_mount(uint8_t *boot_sector, ntfs_volume_t *vol){
    vol->cluster_size = boot_sector[13] * boot_sector[14];
    vol->mft_start_lcn = *((uint64_t*)&boot_sector[48]);
}

