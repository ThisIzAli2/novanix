/**
 * @author Ali Mirmohammad
 * @file tcp.h
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
#ifndef __NOVA_TCP_H
#define __NOVA_TCP_H


#include <common/types.h>

using namespace Novanix::common;

struct tcp_header {
    uint16_t src_port;
    uint16_t dest_port;
    uint32_t seq_num;
    uint32_t ack_num;
    uint8_t data_offset;
    uint8_t flags;
    uint16_t window;
    uint16_t checksum;
    uint16_t urgent;
    uint8_t payload[];
};

VOID tcp_receive(uint32_t src_ip, uint32_t dest_ip, uint8_t* data, uint16_t len);
VOID tcp_send_syn(uint32_t dest_ip, uint16_t src_port, uint16_t dest_port);

#endif /*__NOVA_TCP_H*/