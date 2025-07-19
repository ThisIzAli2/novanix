/**
 * @author Ali Mirmohammad
 * @file driver_match.cpp
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

#include <drivers/driver_match.h>
#include <common/init.hpp>

int match_driver(int found){
    switch(found){
        case INTEL_AC_7260:
            printk(VGA_WHITE,"You have Intel Dual Band Wireless-AC 7260 driver installed",1);
        case INTEL_WIRELESS_8260:
            printk(VGA_WHITE,"You have driver installed",1);
        case INTEL_AX200:
            printk(VGA_WHITE,"You have 	Intel Wi-Fi 6 AX200  driver installed",1);
        case QUALCOMM_ATH9K:
            printk(VGA_WHITE,"You have Qualcomm 	Atheros AR928X Wireless Network Adapter  driver installed",1);
        
    }
}

#include <drivers/driver_match.h>