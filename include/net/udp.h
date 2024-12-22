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
#ifndef __ALINIX_KERNEL_NET_UDP_H
#define __ALINIX_KERNEL_NET_UDP_H

#include <alinix/types.h>
#include <alinix/compiler.h>
#include <net/ip_addr.h>
#include <net/ip.h>
#include <net/err.h>
#include <net/typing.h>
#include <alinix/ip.h>
#include <net/ip_def.h>

typedef void (*udp_recv_fn)(void *arg, struct udp_pcb *pcb, struct pbuf *p,ip_addr_t *addr, uint16_t port);

#ifdef __cplusplus
extern "C"{
#endif


#define UPD_HELEN 8
struct udp_hdr {
  uint16_t src;
  uint16_t dest;  /* src/dest UDP ports */
  uint16_t len;
  uint16_t chksum;
} __attribute__((packed));


#define UDP_FLAGS_NOCHKSUM       0x01U
#define UDP_FLAGS_UDPLITE        0x02U
#define UDP_FLAGS_CONNECTED      0x04U
#define UDP_FLAGS_MULTICAST_LOOP 0x08U

struct udp_pcb {
/* Common members of all PCB types */

/* Protocol specific PCB members */
  // ip_addr_t local_ip;
  struct udp_pcb *next;

  ip_addr_t local_ip;
  ip_addr_t remote_ip;

  unsigned char ttl[4];

  uint8_t flags;
  /** ports are in host byte order */
  uint16_t local_port, remote_port;
  uint8_t so_options;      

#if LWIP_IGMP
  /** outgoing network interface for multicast packets */
  ip_addr_t multicast_ip;
#endif /* LWIP_IGMP */

#if LWIP_UDPLITE
  /** used for UDP_LITE only */
  uint16_t chksum_len_rx, chksum_len_tx;
#endif /* LWIP_UDPLITE */

  /** receive callback function */
  udp_recv_fn recv;
  /** user-supplied argument for the recv callback */
  void *recv_arg;  
};





extern struct udp_pcb *udp_pcbs;


void             udp_remove     (struct udp_pcb *pcb);
err_t            udp_bind       (struct udp_pcb *pcb, ip_addr_t *ipaddr,
                                 uint16_t port);
err_t            udp_connect    (struct udp_pcb *pcb, ip_addr_t *ipaddr,
                                 uint16_t port);
void             udp_disconnect (struct udp_pcb *pcb);
void             udp_recv       (struct udp_pcb *pcb, udp_recv_fn recv,
                                 void *recv_arg);

err_t            udp_sendto     (struct udp_pcb *pcb, struct pbuf *p,
                                 ip_addr_t *dst_ip, uint16_t dst_port);
err_t            udp_send       (struct udp_pcb *pcb, struct pbuf *p);




#if LWIP_CHECKSUM_ON_COPY

err_t            udp_sendto_chksum(struct udp_pcb *pcb, struct pbuf *p,
                                 ip_addr_t *dst_ip, uint16_t dst_port,
                                 uint8_t have_chksum, uint16_t chksum);
err_t            udp_send_chksum(struct udp_pcb *pcb, struct pbuf *p,
                                 uint8_t have_chksum, uint16_t chksum);
#endif /* LWIP_CHECKSUM_ON_COPY */

#define          udp_flags(pcb) ((pcb)->flags)
#define          udp_setflags(pcb, f)  ((pcb)->flags = (f))

/* The following functions are the lower layer interface to UDP. */
void             udp_input      (struct pbuf *p, struct netif *inp);

void             udp_init       (void);

#if UDP_DEBUG
void udp_debug_print(struct udp_hdr *udphdr);
#else
#define udp_debug_print(udphdr)
#endif




#ifdef __cplusplus
}
#endif

#endif /*__ALINIX_KERNEL_NET_UDP_H*/