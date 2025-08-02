/**
 * @author Ali Mirmohammad
 * @file io.h
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

#ifndef __NOVANIX_KERNEL_IO_H
#define __NOVANIX_KERNEL_IO_H

#include <common/init.hpp>

// ATA I/O Ports for Primary Master
#define ATA_DATA        0x1F0
#define ATA_ERROR       0x1F1
#define ATA_SECTOR_COUNT 0x1F2
#define ATA_LBA_LOW     0x1F3
#define ATA_LBA_MID     0x1F4
#define ATA_LBA_HIGH    0x1F5
#define ATA_DRIVE_HEAD  0x1F6
#define ATA_COMMAND     0x1F7
#define ATA_STATUS      0x1F7
#define ATA_WRITE_SECTORS 0x30

int inline ata_wait() {
    int timeout = 1000000; // large count for timeout

    // Wait BSY to clear
    while ((inb(ATA_STATUS) & 0x80) && timeout--) {}
    if (timeout <= 0) return -1; // timeout error

    timeout = 1000000;
    // Wait DRQ to set
    while (!(inb(ATA_STATUS) & 0x08) && timeout--) {}
    if (timeout <= 0) return -2; // timeout error

    return 0; // success
}

// Write 512 bytes (1 sector) to LBA sector 1
void inline ata_write_sector(uint8_t* data) {
    // Send commands to select sector
    outb(ATA_SECTOR_COUNT, 1);       // Write 1 sector
    outb(ATA_LBA_LOW, 1);            // LBA low byte
    outb(ATA_LBA_MID, 0);            // LBA mid byte
    outb(ATA_LBA_HIGH, 0);           // LBA high byte
    outb(ATA_DRIVE_HEAD, 0xE0);      // Master drive, LBA mode

    outb(ATA_COMMAND, ATA_WRITE_SECTORS); // Write command

    ata_wait();  // Wait until ready

    // Write 256 words (512 bytes)
    for (int i = 0; i < 256; ++i) {
        uint16_t word = ((uint16_t)data[2 * i + 1] << 8) | data[2 * i];
        outw(ATA_DATA, word);
    }

    // Flush the write
    ata_wait();
}

int string_to_uint8(const char *str, uint8_t *result) {
    unsigned int value = 0;
    int i = 0;

    if (!str || !result) {
        return -1; // Null pointer error
    }

    // Empty string check
    if (str[0] == '\0') {
        return -1;
    }

    // Parse each character
    while (str[i] != '\0') {
        char c = str[i];
        if (c < '0' || c > '9') {
            return -1; // Invalid character
        }
        value = value * 10 + (c - '0');

        if (value > 255) {
            return -2; // Out of uint8_t range
        }
        i++;
    }

    *result = (uint8_t)value;
    return 0; // Success
}

#endif /*__NOVANIX_KERNEL_IO_H */