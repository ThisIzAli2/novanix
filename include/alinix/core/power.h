/**
 * @file power.h
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
 *  - Kernel Power manager.
*/
#ifndef __ALINIX_KERNEL_CORE_POWER_H
#define __ALINIX_KERNEL_CORE_POWER_H

#include <alinix/types.h>

struct RSDPtr
{
    uint8_t Signature[8];
    uint8_t CheckSum;
    uint8_t OemID[6];
    uint8_t Revision;
    uint32_t* RsdtAddress;
};

struct FACP
{
    uint8_t Signature[4];
    uint32_t Length;
    uint8_t unneded1[40 - 8];
    uint32_t* DSDT;
    uint8_t unneded2[48 - 44];
    uint32_t* SMI_CMD;
    uint8_t ACPI_ENABLE;
    uint8_t ACPI_DISABLE;
    uint8_t unneded3[64 - 54];
    uint32_t* PM1a_CNT_BLK;
    uint32_t* PM1b_CNT_BLK;
    uint8_t unneded4[89 - 72];
    uint8_t PM1_CNT_LEN;
}; 


unsigned int* acpiCheckRSDPtr(unsigned int* ptr);
unsigned int* acpiGetRSDPtr(void);
int acpiCheckHeader(unsigned int* ptr, char* sig);
int acpiEnable(void);
int initAcpi(void);

#endif /*__ALINIX_KERNEL_CORE_POWER_H*/