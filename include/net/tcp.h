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
#ifndef __ALINIX_KERNEL_NET_TCP_H
#define __ALINIX_KERNEL_NET_TCP_H

#include <alinix/types.h>
#include <net/typing.h>
#include <net/ip_def.h>


/** Function prototype for tcp accept callback functions. Called when a new
 * connection can be accepted on a listening pcb.
 *
 * @param arg Additional argument to pass to the callback function (@see tcp_arg())
 * @param newpcb The new connection pcb
 * @param err An error code if there has been an error accepting.
 *            Only return ERR_ABRT if you have called tcp_abort from within the
 *            callback function!
 */
typedef err_t (*tcp_accept_fn)(void *arg, struct tcp_pcb *newpcb, err_t err);

/** Function prototype for tcp receive callback functions. Called when data has
 * been received.
 *
 * @param arg Additional argument to pass to the callback function (@see tcp_arg())
 * @param tpcb The connection pcb which received data
 * @param p The received data (or NULL when the connection has been closed!)
 * @param err An error code if there has been an error receiving
 *            Only return ERR_ABRT if you have called tcp_abort from within the
 *            callback function!
 */
typedef err_t (*tcp_recv_fn)(void *arg, struct tcp_pcb *tpcb,
                             struct pbuf *p, err_t err);

/** Function prototype for tcp sent callback functions. Called when sent data has
 * been acknowledged by the remote side. Use it to free corresponding resources.
 * This also means that the pcb has now space available to send new data.
 *
 * @param arg Additional argument to pass to the callback function (@see tcp_arg())
 * @param tpcb The connection pcb for which data has been acknowledged
 * @param len The amount of bytes acknowledged
 * @return ERR_OK: try to send some data by calling tcp_output
 *            Only return ERR_ABRT if you have called tcp_abort from within the
 *            callback function!
 */
typedef err_t (*tcp_sent_fn)(void *arg, struct tcp_pcb *tpcb,
                              uint16_t len);

/** Function prototype for tcp poll callback functions. Called periodically as
 * specified by @see tcp_poll.
 *
 * @param arg Additional argument to pass to the callback function (@see tcp_arg())
 * @param tpcb tcp pcb
 * @return ERR_OK: try to send some data by calling tcp_output
 *            Only return ERR_ABRT if you have called tcp_abort from within the
 *            callback function!
 */
typedef err_t (*tcp_poll_fn)(void *arg, struct tcp_pcb *tpcb);

/** Function prototype for tcp error callback functions. Called when the pcb
 * receives a RST or is unexpectedly closed for any other reason.
 *
 * @note The corresponding pcb is already freed when this callback is called!
 *
 * @param arg Additional argument to pass to the callback function (@see tcp_arg())
 * @param err Error code to indicate why the pcb has been closed
 *            ERR_ABRT: aborted through tcp_abort or by a TCP timer
 *            ERR_RST: the connection was reset by the remote host
 */
typedef void  (*tcp_err_fn)(void *arg, err_t err);

/** Function prototype for tcp connected callback functions. Called when a pcb
 * is connected to the remote side after initiating a connection attempt by
 * calling tcp_connect().
 *
 * @param arg Additional argument to pass to the callback function (@see tcp_arg())
 * @param tpcb The connection pcb which is connected
 * @param err An unused error code, always ERR_OK currently ;-) TODO!
 *            Only return ERR_ABRT if you have called tcp_abort from within the
 *            callback function!
 *
 * @note When a connection attempt fails, the error callback is currently called!
 */
typedef err_t (*tcp_connected_fn)(void *arg, struct tcp_pcb *tpcb, err_t err);

struct tcp_pcb_listen {  
  int * next;    
  ip_addr_t  local_ip; 
/* Common members of all PCB types */
  // IP_PCB;
/* Protocol specific PCB members */
//   TCP_PCB_COMMON(struct tcp_pcb_listen);

#if TCP_LISTEN_BACKLOG
  uint8_t backlog;
  uint8_t accepts_pending;
#endif /* TCP_LISTEN_BACKLOG */
};

#define TCP_PCB_COMMON(type) \
  type *next; /* for the linked list */ \
  // void *callback_arg; \
  /* the accept callback for listen- and normal pcbs, if LWIP_CALLBACK_API */ \
  DEF_ACCEPT_CALLBACK \
  enum tcp_state state; /* TCP state */ \
  uint8_t prio; \
  /* ports are in host byte order */ \
  uint16_t local_port

struct tcp_pcb {
/** common PCB members */
  // IP_PCB;
/** protocol specific PCB members */
  struct tcp_pcb_listen callback_arg;

  /* ports are in host byte order */
  uint16_t remote_port;

  uint8_t state;
  
  uint8_t flags;
  ip_addr_t local_ip;
  uint8_t next;
#define TF_ACK_DELAY   ((uint8_t)0x01U)   /* Delayed ACK. */
#define TF_ACK_NOW     ((uint8_t)0x02U)   /* Immediate ACK. */
#define TF_INFR        ((uint8_t)0x04U)   /* In fast recovery. */
#define TF_TIMESTAMP   ((uint8_t)0x08U)   /* Timestamp option enabled */
#define TF_RXCLOSED    ((uint8_t)0x10U)   /* rx closed by tcp_shutdown */
#define TF_FIN         ((uint8_t)0x20U)   /* Connection was closed locally (FIN segment enqueued). */
#define TF_NODELAY     ((uint8_t)0x40U)   /* Disable Nagle algorithm */
#define TF_NAGLEMEMERR ((uint8_t)0x80U)   /* nagle enabled, memerr, try to output to prevent delayed ACK to happen */

  /* the rest of the fields are in host byte order
     as we have to do some math with them */

  /* Timers */
  uint8_t polltmr, pollinterval;
  uint8_t last_timer;
  uint32_t tmr;

  /* receiver variables */
  uint32_t rcv_nxt;   /* next seqno expected */
  uint16_t rcv_wnd;   /* receiver window available */
  uint16_t rcv_ann_wnd; /* receiver window to announce */
  uint32_t rcv_ann_right_edge; /* announced right edge of window */

  /* Retransmission timer. */
  sint16_t rtime;

  uint16_t mss;   /* maximum segment size */

  /* RTT (round trip time) estimation variables */
  uint32_t rttest; /* RTT estimate in 500ms ticks */
  uint32_t rtseq;  /* sequence number being timed */
  sint16_t sa, sv; /* @todo document this */

  sint16_t rto;    /* retransmission time-out */
  uint8_t nrtx;    /* number of retransmissions */

  /* fast retransmit/recovery */
  uint8_t dupacks;
  uint32_t lastack; /* Highest acknowledged seqno. */

  /* congestion avoidance/control variables */
  uint16_t cwnd;
  uint16_t ssthresh;

  /* sender variables */
  uint32_t snd_nxt;   /* next new seqno to be sent */
  uint32_t snd_wl1, snd_wl2; /* Sequence and acknowledgement numbers of last
                             window update. */
  uint32_t snd_lbb;       /* Sequence number of next byte to be buffered. */
  uint16_t snd_wnd;   /* sender window */
  uint16_t snd_wnd_max; /* the maximum sender window announced by the remote host */

  uint16_t acked;

  uint16_t snd_buf;   /* Available buffer space for sending (in bytes). */
#define TCP_SNDQUEUELEN_OVERFLOW (0xffffU-3)
  uint16_t snd_queuelen; /* Available buffer space for sending (in tcp_segs). */

#if TCP_OVERSIZE
  /* Extra bytes available at the end of the last pbuf in unsent. */
  uint16_t unsent_oversize;
#endif /* TCP_OVERSIZE */ 

  /* These are ordered by sequence number: */
  struct tcp_seg *unsent;   /* Unsent (queued) segments. */
  struct tcp_seg *unacked;  /* Sent but unacknowledged segments. */
#if TCP_QUEUE_OOSEQ  
  struct tcp_seg *ooseq;    /* Received out of sequence segments. */
#endif /* TCP_QUEUE_OOSEQ */

  struct pbuf *refused_data; /* Data previously received but not yet taken by upper layer */

#if LWIP_CALLBACK_API
  /* Function to be called when more send buffer space is available. */
  tcp_sent_fn sent;
  /* Function to be called when (in-sequence) data has arrived. */
  tcp_recv_fn recv;
  /* Function to be called when a connection has been set up. */
  tcp_connected_fn connected;
  /* Function which is called periodically. */
  tcp_poll_fn poll;
  /* Function to be called whenever a fatal error occurs. */
  tcp_err_fn errf;
#endif /* LWIP_CALLBACK_API */

#if LWIP_TCP_TIMESTAMPS
  uint32_t ts_lastacksent;
  uint32_t ts_recent;
#endif /* LWIP_TCP_TIMESTAMPS */

  /* idle time before KEEPALIVE is sent */
  uint32_t keep_idle;
#if LWIP_TCP_KEEPALIVE
  uint32_t keep_intvl;
  uint32_t keep_cnt;
#endif /* LWIP_TCP_KEEPALIVE */
  
  /* Persist timer counter */
  uint8_t persist_cnt;
  /* Persist timer back-off */
  uint8_t persist_backoff;

  /* KEEPALIVE counter */
  uint8_t keep_cnt_sent;
};


#endif