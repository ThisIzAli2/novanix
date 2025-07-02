#ifndef __NOVA_UDP_H
#define __NOVA_UDP_H




#include <common/types.h>

using namespace Novanix::common;


struct udp_header {
    uint16_t src_port;
    uint16_t dest_port;
    uint16_t length;
    uint16_t checksum;
    uint8_t payload[];
};

void udp_receive(uint32_t src_ip, uint32_t dest_ip, uint8_t* data, uint16_t len);
void udp_send(uint32_t dest_ip, uint16_t src_port, uint16_t dest_port, void* data, uint16_t len);


#endif /*__NOVA_UDP_H*/