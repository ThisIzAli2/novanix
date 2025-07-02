#ifndef __NOVA_KERNEL_NET_H
#define __NOVA_KERNEL_NET_H

#include <common/init.hpp>

#define ETH_TYPE_IPV4 0x0800


struct eth_frame {
    uint8_t dest[6];
    uint8_t src[6];
    uint16_t type;
    uint8_t payload[];
};

void net_init();
void net_receive(uint8_t* data, uint16_t size);
void net_send(uint8_t* dest_mac, uint16_t type, void* payload, uint16_t len);

#endif // __NOVA_KERNEL_NET_H