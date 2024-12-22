/**
 * @author Ali Mirmohammad
 * @file atapi.h
 * *************************************IMPORTANT ALINIX LICENSE TERM********************************************
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

/**
 * @abstraction:
 *  - Kernel API.
*/
#ifndef __ALINIX_KERNEL_AT_API_H
#define __ALINIX_KERNEL_AT_API_H


#include <alinix/port.h>
#include <alinix/types.h>

/**
 * @ref https://wiki.osdev.org/ATAPI
*/
// Handy register number defines
#define DATA 0
#define ERROR_R 1
#define SECTOR_COUNT 2
#define LBA_LOW 3
#define LBA_MID 4
#define LBA_HIGH 5
#define DRIVE_SELECT 6
#define COMMAND_REGISTER 7
 
// Control register defines
#define CONTROL 0x206
 
#define ALTERNATE_STATUS 0


static void ata_io_wait(const uint8_t p);

// Reads sectors starting from lba to buffer
int read_cdrom(uint16_t port, bool slave, uint32_t lba, uint32_t sectors, uint16_t *buffer);



#endif /*__ALINIX_KERNEL_AT_API_H*/