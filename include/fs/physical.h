/**
 * @author Ali Mirmohammad
 * @file physical.h
 ** This file is part of Novanix.

**Novanix is free software: you can redistribute it and/or modify
**it under the terms of the GNU Affero General Public License as published by
**the Free Software Foundation, either version 3 of the License, or
**(at your option) any later version.

**Novanix is distributed in the hope that it will be useful,
**but WITHOUT ANY WARRANTY; without even the implied warranty of
**MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
**GNU Affero General Public License for more details.

**You should have received a copy of the GNU Affero General Public License
**along with Novanix. If not, see <https://www.gnu.org/licenses/>.
*/
#ifndef __NOVANIX_KERNEL_PHYSICAL_KERNEL__H
#define __NOVANIX_KERNEL_PHYSICAL_KERNEL__H


#include <common/init.hpp>

// ATA I/O ports for Primary Channel
#define ATA_DATA       0x1F0
#define ATA_ERROR      0x1F1
#define ATA_SECTOR_CNT 0x1F2
#define ATA_LBA_LOW    0x1F3
#define ATA_LBA_MID    0x1F4
#define ATA_LBA_HIGH   0x1F5
#define ATA_DRIVE_SEL  0x1F6
#define ATA_COMMAND    0x1F7
#define ATA_STATUS     0x1F7
#define ATA_ALT_STATUS 0x3F6

#define ATA_CMD_WRITE_SECTORS 0x30

// Function to write a 512-byte sector to disk
bool __always_inline ata_write_sector(uint32_t lba, const uint8_t* data) {
    // Wait for drive ready
    while (inb(ATA_STATUS) & 0x80); // Wait while busy
    while (!(inb(ATA_STATUS) & 0x08)); // Wait for DRQ

    // Select drive and LBA mode
    outb(ATA_DRIVE_SEL, 0xE0 | ((lba >> 24) & 0x0F));
    outb(ATA_SECTOR_CNT, 1);              // Sector count = 1
    outb(ATA_LBA_LOW, lba & 0xFF);
    outb(ATA_LBA_MID, (lba >> 8) & 0xFF);
    outb(ATA_LBA_HIGH, (lba >> 16) & 0xFF);

    outb(ATA_COMMAND, ATA_CMD_WRITE_SECTORS);

    // Wait for drive ready again
    while (inb(ATA_STATUS) & 0x80);
    while (!(inb(ATA_STATUS) & 0x08));

    // Write 256 words (512 bytes) of data
    for (int i = 0; i < 256; i++) {
        uint16_t word = data[2 * i] | (data[2 * i + 1] << 8);
        outw(ATA_DATA, word);
    }

    // Wait for drive to finish
    while (inb(ATA_STATUS) & 0x80);
    if (inb(ATA_STATUS) & 0x01) {
        // Error bit set
        return false;
    }

    return true;
}


#endif /*__NOVANIX_KERNEL_PHYSICAL_KERNEL__H*/