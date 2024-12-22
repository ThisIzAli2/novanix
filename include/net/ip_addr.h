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
#ifndef __ALINIX_KERNEL_IP_ADDR_NET_H
#define __ALINIX_KERNEL_IP_ADDR_NET_H


#include <alinix/types.h>
#include <alinix/ip.h>
#include <alinix/compiler.h>
#include <net/typing.h>
#include <net/def.h>



#define ip_addr_isany(addr1) ((addr1) == NULL || (addr1)->addr == IPADDR_ANY)
/** 255.255.255.255 */
#define IPADDR_NONE         ((uint32_t)0xffffffffUL)
/** 127.0.0.1 */
#define IPADDR_LOOPBACK     ((uint32_t)0x7f000001UL)
/** 0.0.0.0 */
#define IPADDR_ANY          ((uint32_t)0x00000000UL)
/** 255.255.255.255 */

#define ip_addr_set_any(ipaddr)       ((ipaddr)->addr = IPADDR_ANY)

#define ip_addr_get_network(target, host, netmask) ((target)->addr = ((host)->addr) & ((netmask)->addr))
#define ip_addr_cmp(addr1, addr2) ((addr1)->addr == (addr2)->addr)


#define ip4_addr_get_u32(src_ipaddr) ((src_ipaddr)->addr)
/* Get one byte from the 4-byte address */
#define ip4_addr1(ipaddr) (((uint8_t*)(ipaddr))[0])
#define ip4_addr2(ipaddr) (((uint8_t*)(ipaddr))[1])
#define ip4_addr3(ipaddr) (((uint8_t*)(ipaddr))[2])
#define ip4_addr4(ipaddr) (((uint8_t*)(ipaddr))[3])
#define IPADDR_BROADCAST    ((uint32_t)0xffffffffUL)
#define ip4_addr1_16(ipaddr) ((uint16_t)ip4_addr1(ipaddr))
#define ip4_addr2_16(ipaddr) ((uint16_t)ip4_addr2(ipaddr))
#define ip4_addr3_16(ipaddr) ((uint16_t)ip4_addr3(ipaddr))
#define ip4_addr4_16(ipaddr) ((uint16_t)ip4_addr4(ipaddr))
#define ip_addr_isbroadcast(ipaddr, netif) ip4_addr_isbroadcast((ipaddr)->addr, (netif))
uint8_t ip4_addr_isbroadcast(uint32_t addr, const struct netif *netif);


#define ip_addr_netcmp(addr1, addr2, mask) (((addr1)->addr & \
                                              (mask)->addr) == \
                                             ((addr2)->addr & \
                                              (mask)->addr))

#define ip_addr_copy(dest, src) ((dest).addr = (src).addr)







#define ip_addr_ismulticast(addr1) (((addr1)->addr & PP_HTONL(0xf0000000UL)) == PP_HTONL(0xe0000000UL))



extern const ip_addr_t ip_addr_any;
extern const ip_addr_t ip_addr_broadcast
#define IP_ADDR_ANY         ((ip_addr_t *)&ip_addr_any)
#define IP_ADDR_BROADCAST   ((ip_addr_t *)&ip_addr_broadcast)
;

#define ip4_addr_set_u32(dest_ipaddr, src_u32) ((dest_ipaddr)->addr = (src_u32))



struct ip_addr2 {
  uint16_t addrw[2];
} __attribute__((packed));


// #define ip_addr_set_zero(ipaddr)      do { (ipaddr)->addr = 0; } while(0)
#define ip_addr_set_zero(ipaddr)     


#ifndef IPADDR2_COPY
#define IPADDR2_COPY(dest, src) SMEMCPY(dest, src, sizeof(ip_addr_t))
#endif



#define PP_HTONS(x) ((((x) & 0xff) << 8) | (((x) & 0xff00) >> 8))
#define PP_NTOHS(x) PP_HTONS(x)
#define PP_HTONL(x) ((((x) & 0xff) << 24) | \
                     (((x) & 0xff00) << 8) | \
                     (((x) & 0xff0000UL) >> 8) | \
                     (((x) & 0xff000000UL) >> 24))
#define PP_NTOHL(x) PP_HTONL(x)







#endif /*__ALINIX_KERNEL_IP_ADDR_NET_H*/