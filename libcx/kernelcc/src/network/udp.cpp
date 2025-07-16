/**
 * @file udp.cpp
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
#include <network/udp.h>
#include <common/types.h>

using namespace Novanix::common;

void udp_receive(uint32_t src_ip, uint32_t dest_ip, uint8_t* data, uint16_t len) {
    struct udp_header* udp = (struct udp_header*)data;

    // Novanix::system::printk(VGA_COLOR_WHITE,"rec",1);
        // (src_ip >> 24) & 0xFF, (src_ip >> 16) & 0xFF,
        // (src_ip >> 8) & 0xFF, src_ip & 0xFF,
        // udp->src_port);
    
    // Handle payload...
}