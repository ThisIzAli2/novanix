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
#ifndef __ALINIX_KERNEL_NET_NETIF_H
#define __ALINIX_KERNEL_NET_NETIF_H

// #include <net/err.h>
// #include <net/ip_addr.h>
// #include <net/auto_ip.h>
// #include <alinix/types.h>
// #include <alinix/ip.h>
// #include <net/err.h>
#include <net/ip_addr.h>
#include <alinix/ip.h>
#include <net/err.h>
#include <net/typing.h>
#include <net/auto_ip.h>
#include <net/dhcp.h>
#include <alinix/types.h>





/** Function prototype for netif status- or link-callback functions. */
typedef void (*netif_status_callback_fn)(struct netif *netif);
/** Function prototype for netif igmp_mac_filter functions */


#define ENABLE_LOOPBACK (LWIP_NETIF_LOOPBACK || LWIP_HAVE_LOOPIF)




#define netif_is_up(netif) (((netif)->flags & NETIF_FLAG_UP) ? (uint8_t)1 : (uint8_t)0)


#define NETIF_MAX_HWADDR_LEN 6U


#define NETIF_FLAG_UP           0x01U
/** If set, the netif has broadcast capability.
 * Set by the netif driver in its init function. */
#define NETIF_FLAG_BROADCAST    0x02U
/** If set, the netif is one end of a point-to-point connection.
 * Set by the netif driver in its init function. */
#define NETIF_FLAG_POINTTOPOINT 0x04U
/** If set, the interface is configured using DHCP.
 * Set by the DHCP code when starting or stopping DHCP. */
#define NETIF_FLAG_DHCP         0x08U
/** If set, the interface has an active link
 *  (set by the network interface driver).
 * Either set by the netif driver in its init function (if the link
 * is up at that time) or at a later point once the link comes up
 * (if link detection is supported by the hardware). */
#define NETIF_FLAG_LINK_UP      0x10U
/** If set, the netif is an ethernet device using ARP.
 * Set by the netif driver in its init function.
 * Used to check input packet types and use of DHCP. */
#define NETIF_FLAG_ETHARP       0x20U
/** If set, the netif is an ethernet device. It might not use
 * ARP or TCP/IP if it is used for PPPoE only.
 */
#define NETIF_FLAG_ETHERNET     0x40U
/** If set, the netif has IGMP capability.
 * Set by the netif driver in its init function. */
#define NETIF_FLAG_IGMP         0x80U


struct netif {
  /** pointer to next in linked list */
  struct netif *next;

  /** IP address configuration in network byte order */
  ip_addr_t ip_addr;
  ip_addr_t netmask;
  ip_addr_t gw;
  uint8_t hwaddr_len;

  char* hostname;


  /** This function is called by the network device driver
   *  to pass a packet up the TCP/IP stack. */
  netif_input_fn input;
  /** This function is called by the IP module when it wants
   *  to send a packet on the interface. This function typically
   *  first resolves the hardware address, then sends the packet. */
  netif_output_fn output;
  /** This function is called by the ARP module when it wants
   *  to send a packet on the interface. This function outputs
   *  the pbuf as-is on the link medium. */
  netif_linkoutput_fn linkoutput;
  uint8_t hwaddr[NETIF_MAX_HWADDR_LEN];
  struct autoip *autoip;

  uint8_t flags;
  struct dhcp *dhcp;
  uint16_t mtu;

};





// struct netif {
//   /** pointer to next in linked list */
//   struct netif *next;

//   /** IP address configuration in network byte order */
//   ip_addr_t ip_addr;
//   ip_addr_t netmask;
//   ip_addr_t gw;

//   /** This function is called by the network device driver
//    *  to pass a packet up the TCP/IP stack. */
//   netif_input_fn input;
//   /** This function is called by the IP module when it wants
//    *  to send a packet on the interface. This function typically
//    *  first resolves the hardware address, then sends the packet. */
//   netif_output_fn output;
//   /** This function is called by the ARP module when it wants
//    *  to send a packet on the interface. This function outputs
//    *  the pbuf as-is on the link medium. */
//   netif_linkoutput_fn linkoutput;
// #if LWIP_NETIF_STATUS_CALLBACK
//   /** This function is called when the netif state is set to up or down
//    */
//   netif_status_callback_fn status_callback;
// #endif /* LWIP_NETIF_STATUS_CALLBACK */
// #if LWIP_NETIF_LINK_CALLBACK
//   /** This function is called when the netif link is set to up or down
//    */
//   netif_status_callback_fn link_callback;
// #endif /* LWIP_NETIF_LINK_CALLBACK */
// #if LWIP_NETIF_REMOVE_CALLBACK
//   /** This function is called when the netif has been removed */
//   netif_status_callback_fn remove_callback;
// #endif /* LWIP_NETIF_REMOVE_CALLBACK */
//   /** This field can be set by the device driver and could point
//    *  to state information for the device. */
//   void *state;
//   /** the DHCP client state information for this netif */
//   struct dhcp *dhcp;
//   /** the AutoIP client state information for this netif */
//   struct autoip *autoip;
//   /* the hostname for this netif, NULL is a valid value */
//   char*  hostname;
//   /** maximum transfer unit (in bytes) */
//   uint16_t mtu;
//   /** number of bytes used in hwaddr */
//   uint8_t hwaddr_len;
//   /** link level hardware address of this interface */
//   uint8_t hwaddr[NETIF_MAX_HWADDR_LEN];
//   /** flags (see NETIF_FLAG_ above) */
//   uint8_t flags;
//   /** descriptive abbreviation */
//   char name[2];
//   /** number of this interface */
//   uint8_t num;
//   /** link type (from "snmp_ifType" enum from snmp.h) */
//   uint8_t link_type;
//   /** (estimate) link speed */
//   uint32_t link_speed;
//   /** timestamp at last change made (up/down) */
//   uint32_t ts;
//   /** counters */
//   uint32_t ifinoctets;
//   uint32_t ifinucastpkts;
//   uint32_t ifinnucastpkts;
//   uint32_t ifindiscards;
//   uint32_t ifoutoctets;
//   uint32_t ifoutucastpkts;
//   uint32_t ifoutnucastpkts;
//   uint32_t ifoutdiscards;
//   /** This function could be called to add or delete a entry in the multicast
//       filter table of the ethernet MAC.*/
//   netif_igmp_mac_filter_fn igmp_mac_filter;
//   uint8_t *addr_hint;
//   /* List of packets to be queued for ourselves. */
//   struct pbuf *loop_first;
//   struct pbuf *loop_last;
//   uint16_t loop_cnt_current;
// #endif /* LWIP_LOOPBACK_MAX_PBUFS */
// #endif /* ENABLE_LOOPBACK */
// };


// #define NETIF_INIT_SNMP(netif, type, speed) \
//   /* use "snmp_ifType" enum from snmp.h for "type", snmp_ifType_ethernet_csmacd by example */ \
//   (netif)->link_type = (type);    \
//   /* your link speed here (units: bits per second) */  \
//   (netif)->link_speed = (speed);  \
//   (netif)->ts = 0;              \
//   (netif)->ifinoctets = 0;      \
//   (netif)->ifinucastpkts = 0;   \
//   (netif)->ifinnucastpkts = 0;  \
//   (netif)->ifindiscards = 0;    \
//   (netif)->ifoutoctets = 0;     \
//   (netif)->ifoutucastpkts = 0;  \
//   (netif)->ifoutnucastpkts = 0; \
//   (netif)->ifoutdiscards = 0
// #define NETIF_INIT_SNMP(netif, type, speed)


extern struct netif *netif_list;
// /** The default network interface. */
// extern struct netif *netif_default;


// void netif_init(void);

// struct netif *netif_add(struct netif *netif, ip_addr_t *ipaddr, ip_addr_t *netmask,
//       ip_addr_t *gw, void *state, netif_init_fn init, netif_input_fn input);

// void
// netif_set_addr(struct netif *netif, ip_addr_t *ipaddr, ip_addr_t *netmask,
//       ip_addr_t *gw);
// void netif_remove(struct netif * netif);

// struct netif *netif_find(char *name);

// void netif_set_default(struct netif *netif);

// void netif_set_ipaddr(struct netif *netif, ip_addr_t *ipaddr);
// void netif_set_netmask(struct netif *netif, ip_addr_t *netmask);
// void netif_set_gw(struct netif *netif, ip_addr_t *gw);

// void netif_set_up(struct netif *netif);
// void netif_set_down(struct netif *netif);
// /** Ask if an interface is up */
// #define netif_is_up(netif) (((netif)->flags & NETIF_FLAG_UP) ? (uint8_t)1 : (uint8_t)0)

// void netif_set_status_callback(struct netif *netif, netif_status_callback_fn status_callback);
// void netif_set_remove_callback(struct netif *netif, netif_status_callback_fn remove_callback);

// void netif_set_link_up(struct netif *netif);
// void netif_set_link_down(struct netif *netif);
// /** Ask if a link is up */ 
// #define netif_is_link_up(netif) (((netif)->flags & NETIF_FLAG_LINK_UP) ? (uint8_t)1 : (uint8_t)0)

// void netif_set_link_callback(struct netif *netif, netif_status_callback_fn link_callback);

// #if LWIP_NETIF_HOSTNAME
// #define netif_set_hostname(netif, name) do { if((netif) != NULL) { (netif)->hostname = name; }}while(0)
// #define netif_get_hostname(netif) (((netif) != NULL) ? ((netif)->hostname) : NULL)
// #endif /* LWIP_NETIF_HOSTNAME */

// #define netif_set_igmp_mac_filter(netif, function) do { if((netif) != NULL) { (netif)->igmp_mac_filter = function; }}while(0)
// #define netif_get_igmp_mac_filter(netif) (((netif) != NULL) ? ((netif)->igmp_mac_filter) : NULL)


// err_t netif_loop_output(struct netif *netif, struct pbuf *p, ip_addr_t *dest_ip);
// void netif_poll(struct netif *netif);
// void netif_poll_all(void);

// #define NETIF_SET_HWADDRHINT(netif, hint) ((netif)->addr_hint = (hint))





#endif