/**
 * @author Ali Mirmohammad
 * @file diskio.h
 * @credits Remco123
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
#ifndef __NOVANIX_KERNEL_DISK_IO_H
#define __NOVANIX_KERNEL_DISK_IO_H


#include <common/init.hpp>


#define ATA_DATA      0x1F0
#define ATA_SECTOR_CNT 0x1F2
#define ATA_LBA_LOW    0x1F3
#define ATA_LBA_MID    0x1F4
#define ATA_LBA_HIGH   0x1F5
#define ATA_CMD        0x1F7
#define ATA_READ_CMD   0x20
#define ATA_WRITE_CMD  0x30

#ifndef SECTOR_SIZE
#define SECTOR_SIZE 512
#endif

void __always_inline disk_read(uint32_t lba, uint8_t* buffer, uint32_t count) {
    for(uint32_t i = 0; i < count; i++) {
        outb(ATA_SECTOR_CNT, 1); // sectors to read
        outb(ATA_LBA_LOW, (uint8_t)(lba & 0xFF));
        outb(ATA_LBA_MID, (uint8_t)((lba >> 8) & 0xFF));
        outb(ATA_LBA_HIGH, (uint8_t)((lba >> 16) & 0xFF));
        outb(ATA_CMD, ATA_READ_CMD);

        // Wait for disk ready (simplified)
        while(!(inb(ATA_CMD) & 0x08));

        // Read 256 words = 512 bytes
        for(int j = 0; j < 256; j++) {
            ((uint16_t*)buffer)[j] = inw(ATA_DATA);
        }
        buffer += SECTOR_SIZE;
        lba++;
    }
}

void __always_inline disk_write(uint32_t lba, uint8_t* buffer, uint32_t count) {
    for(uint32_t i = 0; i < count; i++) {
        outb(ATA_SECTOR_CNT, 1); 
        outb(ATA_LBA_LOW, (uint8_t)(lba & 0xFF));
        outb(ATA_LBA_MID, (uint8_t)((lba >> 8) & 0xFF));
        outb(ATA_LBA_HIGH, (uint8_t)((lba >> 16) & 0xFF));
        outb(ATA_CMD, ATA_WRITE_CMD);

        // Wait for disk ready
        while(!(inb(ATA_CMD) & 0x08));

        for(int j = 0; j < 256; j++) {
            outw(ATA_DATA, ((uint16_t*)buffer)[j]);
        }

        buffer += SECTOR_SIZE;
        lba++;
    }
}


#endif /*__NOVANIX_KERNEL_DISK_IO_H*/