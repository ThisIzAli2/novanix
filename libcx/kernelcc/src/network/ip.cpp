/**
 ** This file is part of Novanix.
 @file system.cpp

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
#include <common/types.h>
#include <network/tcp.h>
#include <network/udp.h>


using namespace Novanix::common;


void ip_receive(uint8_t* data, uint16_t size) {
    struct ipv4_header* ip = (struct ipv4_header*)data;

    uint8_t ihl = (ip->ver_ihl & 0x0F) * 4;
    uint16_t total_len = (ip->length >> 8) | (ip->length << 8);

    uint16_t payload_len = total_len - ihl;
    uint8_t* payload = ip->payload;

    if (ip->protocol == IP_PROTOCOL_UDP) {
        udp_receive(ip->src_ip, ip->dest_ip, payload, payload_len);
    } else if (ip->protocol == IP_PROTOCOL_TCP) {
        tcp_receive(ip->src_ip, ip->dest_ip, payload, payload_len);
    }
}