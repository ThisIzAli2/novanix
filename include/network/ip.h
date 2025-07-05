/**
 * @author Ali Mirmohammad
 * @file ip.h
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
#ifndef __NOVA_KERNEL_IP_H
#define __NOVA_KERNEL_IP_H


#include <common/types.h>

using namespace Novanix::common;

#define IP_PROTOCOL_UDP 17
#define IP_PROTOCOL_TCP 6

struct ipv4_header {
    uint8_t ver_ihl;
    uint8_t tos;
    uint16_t length;
    uint16_t id;
    uint16_t flags_fragment;
    uint8_t ttl;
    uint8_t protocol;
    uint16_t checksum;
    uint32_t src_ip;
    uint32_t dest_ip;
    uint8_t payload[];
};

void ip_receive(uint8_t* data, uint16_t size);
void ip_send(uint32_t dest_ip, uint8_t protocol, void* payload, uint16_t size);


#endif // __NOVA_KERNEL_IP_H