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



#endif /*__NOVANIX_KERNEL_DRIVERS_VENDORS_H*/