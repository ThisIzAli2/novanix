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
#ifndef __ALINIX_KERNEL_NET_TCP_IMPL_H
#define __ALINIX_KERNEL_NET_TCP_IMPL_H

#include <alinix/types.h>
#include <net/tcp.h>
#include <net/ip_addr.h>


void tcp_pcb_purge(struct tcp_pcb *pcb);

extern union tcp_listen_pcbs_t tcp_listen_pcbs;

extern uint8_t tcp_active_pcbs_changed;
extern struct tcp_pcb *tcp_active_pcbs;  /* List of all TCP PCBs that are in a
              state in which they accept or send
              data. */


union tcp_listen_pcbs_t { /* List of all TCP PCBs in LISTEN state. */
  struct tcp_pcb_listen *listen_pcbs; 
  struct tcp_pcb *pcbs;
};


#define TCP_PCB_REMOVE_ACTIVE(pcb)                 \
  do {                                             \
    tcp_pcb_remove(&tcp_active_pcbs, pcb);         \
    tcp_active_pcbs_changed = 1;                   \
  } while (0)



struct tcp_seg {
  struct tcp_seg *next;    /* used when putting segements on a queue */
  struct pbuf *p;          /* buffer containing data + TCP header */
  uint16_t len;               /* the TCP length of this segment */
#if TCP_OVERSIZE_DBGCHECK
  uint16_t oversize_left;     /* Extra bytes available at the end of the last
                              pbuf in unsent (used for asserting vs.
                              tcp_pcb.unsent_oversized only) */
#endif /* TCP_OVERSIZE_DBGCHECK */ 
#if TCP_CHECKSUM_ON_COPY
  uint16_t chksum;
  uint8_t  chksum_swapped;
#endif /* TCP_CHECKSUM_ON_COPY */
  uint8_t  flags;
#define TF_SEG_OPTS_MSS         (uint8_t)0x01U /* Include MSS option. */
#define TF_SEG_OPTS_TS          (uint8_t)0x02U /* Include timestamp option. */
#define TF_SEG_DATA_CHECKSUMMED (uint8_t)0x04U /* ALL data (not the header) is
                                               checksummed into 'chksum' */
  struct tcp_hdr *tcphdr;  /* the TCP header */
};


#define TCP_EVENT_ERR(errf,arg,err)                            \
  do {                                                         \
    if((errf) != NULL)                                         \
      (errf)((arg),(err));                                     \
  } while (0)


#define TCP_RMV(pcbs, npcb)                        \
  do {                                             \
    if(*(pcbs) == (npcb)) {                        \
      (*(pcbs)) = (*pcbs)->next;                   \
    }                                              \
    else {                                         \
      for(tcp_tmp_pcb = *pcbs;                     \
          tcp_tmp_pcb != NULL;                     \
          tcp_tmp_pcb = tcp_tmp_pcb->next) {       \
        if(tcp_tmp_pcb->next == (npcb)) {          \
          tcp_tmp_pcb->next = (npcb)->next;        \
          break;                                   \
        }                                          \
      }                                            \
    }                                              \
    (npcb)->next = NULL;                           \
  } while(0)


#endif