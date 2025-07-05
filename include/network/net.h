/**
 * @author Ali Mirmohammad
 * @file net.h
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
#ifndef __NOVA_KERNEL_NET_H
#define __NOVA_KERNEL_NET_H

#include <common/types.h>

using namespace Novanix::common;

#define ETH_TYPE_IPV4 0x0800


struct eth_frame {
    uint8_t dest[6];
    uint8_t src[6];
    uint16_t type;
    uint8_t payload[];
};

void net_init();
void net_receive(uint8_t* data, uint16_t size);
void net_send(uint8_t* dest_mac, uint16_t type, void* payload, uint16_t len);

#endif // __NOVA_KERNEL_NET_H