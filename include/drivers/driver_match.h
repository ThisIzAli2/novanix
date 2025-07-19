/**
 * @author Ali Mirmohammad
 * @file driver_match.h
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

#ifndef __NOVANIX_KERNEL_DRIVERS_DRIVER_MATCH_H
#define __NOVANIX_KERNEL_DRIVERS_DRIVER_MATCH_H

#include <drivers/vendors.h>

typedef enum {
    DRIVER_UNKNOWN = 0,

    // Intel
    DRIVER_INTEL_WIFI,
    DRIVER_INTEL_E1000,
    DRIVER_INTEL_IGB,
    DRIVER_INTEL_IWLWIFI,  // Newer Wi-Fi stack

    // Qualcomm / Atheros
    DRIVER_ATHEROS_WIFI,
    DRIVER_QCA_WIFI,

    // Broadcom
    DRIVER_BRCM_WIFI,
    DRIVER_BRCM_43XX,

    // Realtek
    DRIVER_RTL8139,
    DRIVER_RTL8168,
    DRIVER_RTL8821CE,
    DRIVER_RTL_WIFI_GENERIC,

    // MediaTek / Ralink
    DRIVER_MEDIATEK_WIFI,
    DRIVER_RALINK_RT2800,

    // Marvell
    DRIVER_MARVELL_YUKON,

    // NVIDIA (Network, rarely Wi-Fi)
    DRIVER_NVIDIA_NFORCE,

    // VIA
    DRIVER_VIA_RHINE,

    // Fallback
    DRIVER_GENERIC_NETWORK
} pci_driver_type;

int match_driver(int found);


#endif /*__NOVANIX_KERNEL_DRIVERS_DRIVER_MATCH_H*/