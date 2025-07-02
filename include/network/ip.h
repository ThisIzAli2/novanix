#ifndef __NOVA_KERNEL_IP_H
#define __NOVA_KERNEL_IP_H


#include <common/init.hpp>

#define IP_PROTOCOL_UDP 17
#define IP_PROTOCOL_TCP 6

struct ipv4_header {
    uint8_t ver_ihl;
    uint8_t tos;
    uint16_t length;
    uint16_t id;
    uint16_t flags_fragment;
    uint8_t ttl;
    uint8_t protocol;
    uint16_t checksum;
    uint32_t src_ip;
    uint32_t dest_ip;
    uint8_t payload[];
};

void ip_receive(uint8_t* data, uint16_t size);
void ip_send(uint32_t dest_ip, uint8_t protocol, void* payload, uint16_t size);


#endif // __NOVA_KERNEL_IP_H