/**
 * @author Ali Mirmohammad
 * @file rtc.h
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
 * @abstract:
 *  - Kernel RTC networking device.
 *  - header implementations.
*/

#ifndef __ALINIX_KERNEL_RTC_H
#define __ALINIX_KERNEL_RTC_H

#include <alinix/types.h>

#define CURRENT_YEAR 2024

bool UpdateInProgress();

uint8_t ReadRegister(int reg);
/// @brief //////////////
// Functions to get the data and time for the kernel time settings.
uint32_t GetSecond();
uint32_t GetMinute();
uint32_t GetHour();
uint32_t GetDay();
uint32_t GetMonth();
uint32_t GetYear();
//////////////////////////////////
#endif /*__ALINIX_KERNEL_RTC_H*/