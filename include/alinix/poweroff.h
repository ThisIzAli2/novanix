/**
 * @author Ali Mirmohammad
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
 * @file poweroff.h
 * @abstraction:
 *  - Kernel power off implemented in this header file.
*/

#ifndef __ALINIX_KERNEL_POWER_OFF_H
#define __ALINIX_KERNEL_POWER_OFF_H

#include <alinix/types.h>
#include <alinix/core/power.h>


/**
 * @brief Structure of power off operations.
*/
struct powerOff{
    u16 *SMI_CMD;
    byte ACPI_ENABLE;
    byte ACPI_DISABLE;
    u16 *PM1a_CNT;
    u16 *PM1b_CNT;
    char SLP_TYPa;
    char SLP_TYPb;
    char SLP_EN;
    char SCI_EN;
    byte PM1_CNT_LEN;
};

#endif /*__ALINIX_KERNEL_POWER_OFF_H*/