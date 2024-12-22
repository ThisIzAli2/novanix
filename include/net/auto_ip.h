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
#ifndef __ALINIX_KERNEL_NET_AUTO_IP_H
#define __ALINIX_KERNEL_NET_AUTO_IP_H

#include <alinix/types.h>
#include <net/ip_addr.h>
#include <net/netif.h>
#include <net/typing.h>

#define PROBE_WAIT               1   /* second   (initial random delay)                 */
#define PROBE_MIN                1   /* second   (minimum delay till repeated probe)    */
#define PROBE_MAX                2   /* seconds  (maximum delay till repeated probe)    */
#define PROBE_NUM                3   /*          (number of probe packets)              */
#define ANNOUNCE_NUM             2   /*          (number of announcement packets)       */
#define ANNOUNCE_INTERVAL        2   /* seconds  (time between announcement packets)    */
#define ANNOUNCE_WAIT            2   /* seconds  (delay before announcing)              */
#define MAX_CONFLICTS            10  /*          (max conflicts before rate limiting)   */
#define RATE_LIMIT_INTERVAL      60  /* seconds  (delay between successive attempts)    */
#define DEFEND_INTERVAL          10  /* seconds  (min. wait between defensive ARPs)  */
#define AUTOIP_STATE_OFF         0
#define AUTOIP_STATE_PROBING     1
#define AUTOIP_STATE_ANNOUNCING  2
#define AUTOIP_STATE_BOUND       3

#define AUTOIP_TMR_INTERVAL      100
#define AUTOIP_TICKS_PER_SECOND (1000 / AUTOIP_TMR_INTERVAL)

struct autoip
{
  //? Change to uint 8_t when we support multiple netifs
  uint64_t llipaddr;       /* the currently selected, probed, announced or used LL IP-Address */
  uint8_t state;               /* current AutoIP state machine state */
  uint8_t sent_num;            /* sent number of probes or announces, dependent on state */
  uint16_t ttw;                /* ticks to wait, tick is AUTOIP_TMR_INTERVAL long */
  uint8_t lastconflict;        /* ticks until a conflict can be solved by defending */
  uint8_t tried_llipaddr;      /* total number of probed/used Link Local IP-Addresses */
};

err_t 
autoip_start(struct netif *netif);


#endif // __ALINIX_KERNEL_NET_AUTO_IP_H