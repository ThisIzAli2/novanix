/**
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
#ifndef __ALINIX_KERNEL_ETH_ARP_H_NET
#define __ALINIX_KERNEL_ETH_ARP_H_NET

#include <alinix/compiler.h>
#include <alinix/types.h>
#include <net/ip_addr.h>
#include <net/netif.h>
#ifndef ETHARP_HWADDR_LEN
#define ETHARP_HWADDR_LEN     6
#endif

#define etharp_gratuitous(netif) etharp_request((netif), &(netif)->ip_addr)

err_t etharp_request(struct netif *netif, ip_addr_t *ipaddr);

#define SIZEOF_ETH_HDR (14 + ETH_PAD_SIZE)


#define ETHTYPE_ARP       0x0806U
#define ETHTYPE_IP        0x0800U
#define ETHTYPE_VLAN      0x8100U
#define ETHTYPE_PPPOEDISC 0x8863U  /* PPP Over Ethernet Discovery Stage */
#define ETHTYPE_PPPOE     0x8864U  /* PPP Over Ethernet Session Stage */

#define SIZEOF_ETHARP_HDR 28
#define SIZEOF_ETHARP_PACKET (SIZEOF_ETH_HDR + SIZEOF_ETHARP_HDR)



PACK_STRUCT_BEGIN
struct eth_addr {
  PACK_STRUCT_FIELD(uint8_t addr[ETHARP_HWADDR_LEN]);
} __attribute__((packed));
PACK_STRUCT_END

extern const struct eth_addr ethbroadcast, ethzero;

err_t etharp_query(struct netif *netif, ip_addr_t *ipaddr, struct pbuf *q);


PACK_STRUCT_BEGIN
/** the ARP message, see RFC 826 ("Packet format") */
struct etharp_hdr {
  PACK_STRUCT_FIELD(uint16_t hwtype);
  PACK_STRUCT_FIELD(uint16_t proto);
  PACK_STRUCT_FIELD(uint8_t  hwlen);
  PACK_STRUCT_FIELD(uint8_t  protolen);
  PACK_STRUCT_FIELD(uint16_t opcode);
  PACK_STRUCT_FIELD(struct eth_addr shwaddr);
  PACK_STRUCT_FIELD(struct ip_addr2 sipaddr);
  PACK_STRUCT_FIELD(struct eth_addr dhwaddr);
  PACK_STRUCT_FIELD(struct ip_addr2 dipaddr);
} __attribute__((packed));
PACK_STRUCT_END

struct eth_hdr {
#if ETH_PAD_SIZE
  PACK_STRUCT_FIELD(uint8_t padding[ETH_PAD_SIZE]);
#endif
  PACK_STRUCT_FIELD(struct eth_addr dest);
  PACK_STRUCT_FIELD(struct eth_addr src);
  PACK_STRUCT_FIELD(uint16_t type);
} __attribute__((packed));
PACK_STRUCT_END



#ifndef ETHADDR16_COPY
#define ETHADDR16_COPY(src, dst)  SMEMCPY(src, dst, ETHARP_HWADDR_LEN)
#endif

void etharp_cleanup_netif(struct netif *netif);


#endif // __ALINIX_KERNEL_ETH_ARP_H_NET