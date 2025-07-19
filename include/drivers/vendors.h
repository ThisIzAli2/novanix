/**
 * @author Ali Mirmohammad
 * @file vendors.h
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
#ifndef __NOVANIX_KERNEL_DRIVERS_VENDORS_H
#define __NOVANIX_KERNEL_DRIVERS_VENDORS_H


#define INTEL_AC_7260 0x08B1
#define INTEL_WIRELESS_8260 0x24F3
#define INTEL_AX200	0x2723	


/**
 * 🟣 Qualcomm Atheros 
 */


#define QUALCOMM_ATH9K 0x0030
#define QUALCOMM_ATH10K 0x003E
#define QUALCOMM_QCA9377 QUALCOMM_QCA9377

/**
 * The following vendors are defined for the networks vendors.
 */

#define INTEL_VENDOR_ID         0x8086
#define QUALCOMM_VENDOR_ID      0x168C   // Atheros
#define BROADCOM_VENDOR_ID      0x14E4
#define REALTEK_VENDOR_ID       0x10EC
#define MEDIATEK_VENDOR_ID      0x14C3
#define RALINK_VENDOR_ID        0x1814   // Now part of MediaTek
#define MARVELL_VENDOR_ID       0x11AB
#define CISCO_VENDOR_ID         0x1137
#define MEDIATEK_RALINK_ID      0x1814   // Ralink rebadged
#define NVIDIA_NETWORK_VENDOR   0x10DE

/**
 * The following vendors are for graphics
 */

#define NVIDIA_VENDOR_ID        0x10DE
#define AMD_VENDOR_ID           0x1002
#define ATI_VENDOR_ID           0x1002   // (legacy AMD)
#define INTEL_GPU_VENDOR_ID     0x8086   // Shared with Intel CPUs

/**
 * Thw following vendors are for Storage 
 */

#define SANDISK_VENDOR_ID       0x15B7
#define SAMSUNG_VENDOR_ID       0x144D
#define KINGSTON_VENDOR_ID      0x2646
#define WESTERN_DIGITAL_ID      0x1058
#define SEAGATE_VENDOR_ID       0x1BB1
#define ADAPTEC_VENDOR_ID       0x9005

/**
 * The following vendors are for the motherboard and chipsets.
 */

#define AMD_VENDOR_ID           0x1022
#define VIA_VENDOR_ID           0x1106
#define SIS_VENDOR_ID           0x1039
#define NVIDIA_VENDOR_ID        0x10DE   // Yes, also chipset
#define ALI_VENDOR_ID           0x10B9
#define IBM_VENDOR_ID           0x1014
#define HP_VENDOR_ID            0x103C
#define DELL_VENDOR_ID          0x1028

/**
 * The bellow vendors are for USB 
 */

#define NEC_VENDOR_ID           0x1033
#define RENESAS_VENDOR_ID       0x1912
#define ASMEDIA_VENDOR_ID       0x1B21
#define TEXAS_INSTRUMENTS_ID    0x104C
#define LOGITECH_VENDOR_ID      0x046D
#define APPLE_VENDOR_ID         0x05AC

/**
 * The below vendors are for wireless communication
 */

#define MEDIATEK_VENDOR_ID      0x14C3
#define FOXCONN_VENDOR_ID       0x105B
#define DELL_WIFI_VENDOR_ID     0x1028
#define HP_WIFI_VENDOR_ID       0x103C


#endif /*__NOVANIX_KERNEL_DRIVERS_VENDORS_H*/