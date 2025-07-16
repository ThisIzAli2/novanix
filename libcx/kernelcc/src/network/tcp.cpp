/**
 * @file tcp.cpp
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
#include <network/tcp.h>
#include <common/types.h>
#include <system/log.h>

using namespace Novanix::common;

void tcp_receive(uint32_t src_ip, uint32_t dest_ip, uint8_t* data, uint16_t len) {
    struct tcp_header* tcp = (struct tcp_header*)data;

    Novanix::system::printk(Novanix::system::VGA_COLOR_WHITE,"Rec TCP",1);

}