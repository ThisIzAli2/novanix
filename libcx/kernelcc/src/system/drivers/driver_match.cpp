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
        case QUALCOMM_ATH10K:
            printk(VGA_WHITE,"You have Qualcomm 	Qualcomm Atheros QCA988x   driver installed",1);
        case QUALCOMM_QCA9377:
            printk(VGA_WHITE,"You have Qualcomm 		Qualcomm Atheros QCA9377    driver installed",1);
        case BROADCOM_BCM4311:
            printk(VGA_WHITE,"You have Qualcomm Broadcom BCM4311    driver installed",1);
        case BROADCOM_BCM4322:
            printk(VGA_WHITE,"You have Qualcomm 	Broadcom BCM4322    driver installed",1);
        case BROADCOM_BCM4352:
            printk(VGA_WHITE,"You have Qualcomm 		Broadcom BCM4352    driver installed",1);
        case MEDIATEK_MT7610U:
            printk(VGA_WHITE,"You have Qualcomm MediaTek MT7610U   driver installed",1);
        case MEDIATEK_MT7601U:
            printk(VGA_WHITE,"You have Qualcomm 	MediaTek MT7601U   driver installed",1);
        case REALTEK_RTL8723BE:
            printk(VGA_WHITE,"You have  RTL8723BE PCIe Wireless Adapter  driver installed",1);
        case REALTEK_RTL8192CE:
            printk(VGA_WHITE,"You have RTL8192CE Wireless Adapter driver installed",1);
        case REALTEK_RTL8821AE:
            printk(VGA_WHITE,"You have 	Realtek RTL8821AE  driver installed",1);
        case MARVELL_88W8897:
            printk(VGA_WHITE,"You have 	Marvell Avastar 88W8897  driver installed",1);
        case INTEL_VENDOR_ID:
            printk(VGA_WHITE,"You have 	Common for both wired (Ethernet) and wireless devices driver installed",1);
        case QUALCOMM_VENDOR_ID:
            printk(VGA_WHITE,"You have 	Acquired Atheros driver installed",1);
        case BROADCOM_VENDOR_ID:
            printk(VGA_WHITE,"Broadcom Inc.	NIC card installed",1);
        case REALTEK_VENDOR_ID:
            printk(VGA_WHITE,"Realtek Semiconductor Corp. driver installed.",1);
        case MEDIATEK_VENDOR_ID:
            printk(VGA_WHITE,"MediaTek Inc. driver installed",1);
        case RALINK_VENDOR_ID:
            printk(VGA_WHITE,"Ralink Technology Corp.	driver installed",1);
        case MARVELL_VENDOR_ID:
            printk(VGA_WHITE,"	Marvell Technology Group driver installed",1);
    }
}
