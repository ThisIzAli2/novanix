/**
 ** This file is part of AliNix.

**AliNix is free software: you can redistribute it and/or modify
**it under the terms of the GNU Affero General Public License as published by
**the Free Software Foundation, either version 3 of the License, or
**(at your option) any later version.

**AliNix is distributed in the hope that it will be useful,
**but WITHOUT ANY WARRANTY; without even the implied warranty of
**MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
**GNU Affero General Public License for more details.

**You should have received a copy of the GNU Affero General Public License
**along with AliNix. If not, see <https://www.gnu.org/licenses/>.
*/

#ifndef ATA_H
#define ATA_H

#include <types.h>
/**
 * represents the I/O port address for accessing the primary data register of the ATA controller.
 * @note reads the primary errors and etc from the primary ATA hard drive
*/
#define ATA_PRIMARY_DATA            0x1F0
#define ATA_PRIMARY_ERROR           0x1F1
#define ATA_PRIMARY_SECTORS         0x1F2
/**
 * @note access lower 8 bits of LBA for the primary ATA hard drive
*/
#define ATA_PRIMARY_LBA_LOW         0x1F3

/**
 * @note This will define the upper 8 bits of LBA for the primary ATA hard drive
*/

#define ATA_PRIMARY_LBA_MID         0x1F4

/**
 * @note This will define the upper 8 bits of LBA for the primary ATA hard drive
*/

#define ATA_PRIMARY_LBA_HIGH        0x1F5

/**
 * @note other ATA macros
*/

#define ATA_PRIMARY_DRIVE_SEL       0x1F6
#define ATA_PRIMARY_STATUS          0x1F7
#define ATA_PRIMARY_IRQ             14

/**
 * @note other ATA macros (secondary)
*/

#define ATA_SECONDARY_DATA          0x170
#define ATA_SECONDARY_ERR           0x171
#define ATA_SECONDARY_SECTORS       0x172
#define ATA_SECONDARY_LBA_LOW       0x173
#define ATA_SECONDARY_LBA_MID       0x174
#define ATA_SECONDARY_LBA_HIGH      0x175
#define ATA_SECONDARY_DRIVE_SEL     0x176
#define ATA_SECONDARY_STATUS        0x177
#define ATA_SECONDARY_IRQ           15

#define ATA_IDENTIFY                0xEC


typedef struct ata_drive{
    int present;
    int type; // master or slave
    uint32_t data_reg;
    uint32_t err_reg;
    uint32_t sectors_reg;
    uint32_t lba_low_reg;
    uint32_t lba_mid_reg;
    uint32_t lba_high_reg;
    uint32_t sel_reg;
    uint32_t status_reg;
    uint32_t irq_num;
    int lba_mode; // 1 LBA48 else LBA28
    uint32_t total_sectors_28;
    uint64_t total_sectors_48;
}drive_t;

typedef struct ata_drives{
    drive_t cur_hdd;
    drive_t primary_master;
    drive_t primary_slave;
    drive_t secondary_master;
    drive_t secondary_slave;
}ata_drives_t;


void ata_init();
void ata_wait_for_irq();
void ata_info_fill(drive_t *drive, int type, uint32_t data, uint32_t err, uint32_t sect, uint32_t lba_low, uint32_t lba_mid, uint32_t lba_high, uint32_t sel, uint32_t status, uint32_t irq);
void identify(drive_t *drive);
void delay_400ns();
char *ata_read_sector(int lba);


#endif // ATA_H