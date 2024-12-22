/**
 * @author Ali Mirmohammad
 * @file ip.h
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
 *  - Ip Address util defined in this header file.
*/
#ifndef __ALINIX_KERNEL_IP_H
#define __ALINIX_KERNEL_IP_H

//////////////////////////////////
// Ip headers should be included here
#include <net/ip.h>
#include <net/auto_ip.h>
#include <net/ip_addr.h>
#include <net/ip_frag.h>
//////////////////////////////////
// Generic  functions to handle IP addresses
#include <alinix/types.h>
#include <alinix/compiler.h>
//////////////////////////////////


/**
 * @brief Some useful macros.
*/
#define SOF_BROADCAST     0x20U  /* permit to send and to receive broadcast messages (see IP_SOF_BROADCAST option) */

#define IP_PCB_ADDRHINT ;uint8_t addr_hint
#define ip_set_option(pcb, opt)   ((pcb)->so_options |= (opt))

#define snmp_insert_iprteidx_tree(dflt, ni)
#define ip_addr_set(dest, src) ((dest)->addr = \
                                    ((src) == NULL ? 0 : \
                                    (src)->addr))

#define snmp_delete_iprteidx_tree(dflt, ni)





#endif /*__ALINIX_KERNEL_IP_H*/