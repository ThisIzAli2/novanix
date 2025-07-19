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
            printk(VGA_WHITE,"You have Intel Dual Band Wireless-AC 7260 driver Found",1);
        case INTEL_WIRELESS_8260:
            printk(VGA_WHITE,"You have driver Found",1);
        case INTEL_AX200:
            printk(VGA_WHITE,"You have 	Intel Wi-Fi 6 AX200  driver Found",1);
        case QUALCOMM_ATH9K:
            printk(VGA_WHITE,"You have Qualcomm 	Atheros AR928X Wireless Network Adapter  driver Found",1);
        case QUALCOMM_ATH10K:
            printk(VGA_WHITE,"You have Qualcomm 	Qualcomm Atheros QCA988x   driver Found",1);
        case QUALCOMM_QCA9377:
            printk(VGA_WHITE,"You have Qualcomm 		Qualcomm Atheros QCA9377    driver Found",1);
        case BROADCOM_BCM4311:
            printk(VGA_WHITE,"You have Qualcomm Broadcom BCM4311    driver Found",1);
        case BROADCOM_BCM4322:
            printk(VGA_WHITE,"You have Qualcomm 	Broadcom BCM4322    driver Found",1);
        case BROADCOM_BCM4352:
            printk(VGA_WHITE,"You have Qualcomm 		Broadcom BCM4352    driver Found",1);
        case MEDIATEK_MT7610U:
            printk(VGA_WHITE,"You have Qualcomm MediaTek MT7610U   driver Found",1);
        case MEDIATEK_MT7601U:
            printk(VGA_WHITE,"You have Qualcomm 	MediaTek MT7601U   driver Found",1);
        case REALTEK_RTL8723BE:
            printk(VGA_WHITE,"You have  RTL8723BE PCIe Wireless Adapter  driver Found",1);
        case REALTEK_RTL8192CE:
            printk(VGA_WHITE,"You have RTL8192CE Wireless Adapter driver Found",1);
        case REALTEK_RTL8821AE:
            printk(VGA_WHITE,"You have 	Realtek RTL8821AE  driver Found",1);
        case MARVELL_88W8897:
            printk(VGA_WHITE,"You have 	Marvell Avastar 88W8897  driver Found",1);
        case INTEL_VENDOR_ID:
            printk(VGA_WHITE,"You have 	Common for both wired (Ethernet) and wireless devices driver Found",1);
        case QUALCOMM_VENDOR_ID:
            printk(VGA_WHITE,"You have 	Acquired Atheros driver Found",1);
        case BROADCOM_VENDOR_ID:
            printk(VGA_WHITE,"Broadcom Inc.	NIC card Found",1);
        case REALTEK_VENDOR_ID:
            printk(VGA_WHITE,"Realtek Semiconductor Corp. driver Found.",1);
        case MEDIATEK_VENDOR_ID:
            printk(VGA_WHITE,"MediaTek Inc. driver Found",1);
        case RALINK_VENDOR_ID:
            printk(VGA_WHITE,"Ralink Technology Corp.	driver Found",1);
        case MARVELL_VENDOR_ID:
            printk(VGA_WHITE,"	Marvell Technology Group driver Found",1);
        case CISCO_VENDOR_ID:
            printk(VGA_WHITE,"Cisco Systems, Inc.	driver Found",1);
        case NVIDIA_NETWORK_VENDOR:
            printk(VGA_WHITE,"Nvidia network Ethernet driver Found",1);
        case AMD_VENDOR_ID:
            printk(VGA_WHITE,"	AMD Inc. driver found",1);
        case ATI_VENDOR_ID:
            printk(VGA_WHITE,"		ATI Technologies  driver found",1);
        case SANDISK_VENDOR_ID:
            printk(VGA_WHITE,"	SanDisk Corporation driver found",1);
        case SAMSUNG_VENDOR_ID:
            printk(VGA_WHITE,"	Samsung Electronics driver found",1);
        case KINGSTON_VENDOR_ID:
            printk(VGA_WHITE,"		Kingston Technology driver found",1);
        case WESTERN_DIGITAL_ID:
            printk(VGA_WHITE,"		Western Digital Corp driver found",1);
        case SEAGATE_VENDOR_ID:
            printk(VGA_WHITE,"		Seagate Technology driver found",1);
    }
}
