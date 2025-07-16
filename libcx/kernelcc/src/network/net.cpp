/**
 * @file net.cpp
 * @author Ali Mirmohammad
 * 
 ** This file is part of Novanix.

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
#include <network/ip.h>
#include <network/net.h>
#include <common/types.h>




using namespace Novanix::common;

VOID net_receive(uint8_t* data,uint16_t size){
    struct eth_frame* frame = (struct eth_frame*)data;
    uint16_t eth_type = (frame->type << 8) | (frame->type >> 8); // Swap endian

    if (eth_type == ETH_TYPE_IPV4) {
        ip_receive(frame->payload, size - sizeof(struct eth_frame));
    }
}


