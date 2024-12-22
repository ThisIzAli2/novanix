/**
 * @author Ali Mirmohammad
 * @file init.h
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
 *  - used to initiate the kernel modules.
*/

#ifndef _ALINIX_INIT_H
#define _ALINIX_INIT_H


/**
 * @brief This file should be used to initiate the kernel Entry point.
*/

#include <alinix/types.h>
#include <alinix/physicalmemory.h>


/**
 * @brief Header files for kernel initiation
*/

#include <alinix/idt.h>
#include <alinix/assembly.h>
#include <alinix/audit.h>
#include <alinix/security.h>
#include <alinix/inet.h>
#include <alinix/arch.h>
#include <alinix/bootconsole.h>
#include <alinix/etherdevice.h>
#include <alinix/if_arp.h>
#include <alinix/swait.h>
#include <alinix/settings.h>
#include <alinix/irq.h>
#include <alinix/ip.h>
#include <alinix/compiler.h>
#include <alinix/gui/window.h>
#include <alinix/gui/canvas.h>
#include <alinix/gui/colors.h>
#include <alinix/gui/directgui.h>
#include <alinix/gui/fonts/font.h>
#include <alinix/gui/gui.h>
#include <alinix/netif.h>
#include <net/arp.h>
#include <net/auto_ip.h>
#include <net/icmp.h>
#include <net/tcp.h>
#include <net/tcp_impl.h>
#include <net/dns.h>
#include <net/device_net.h>
#include <net/def.h>
#include <net/dhcp.h>
#include <alinix/xheap.h>
#include <alinix/security/apparmor/audit.h>
#include <alinix/graphics/model.h>
#include <asm/hwrpb.h>
#include <asm/setup.h>
#include <alinix/log.h>
#include <alinix/enums.h>
#include <alinix/bootconsole.h>
#include <alinix/keyboard.h>
#include <alinix/beep.h>
#include <alinix/progress.h>
#include <alinix/print.h>
#include <alinix/convert.h>
#include <alinix/panic.h>

#define __init		__section(".init.text")
// static void Initialize();
CommandBlockWrapper SCSIPrepareCommandBlock(uint8_t command, int length, uint64_t lba, int sectors);
// bool ResetRecovery();
// bool SCSIRequest(CommandBlockWrapper* request, uint8_t* dataPointer, int dataLength);
void DeInitialize();
char ReadSector(uint32_t lba, uint8_t* buf);
char WriteSector(uint32_t lba, uint8_t* buf);


#endif /*_ALINIX_INIT_H*/