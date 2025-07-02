#ifndef __NOVA_TCP_H
#define __NOVA_TCP_H


#include <common/init.hpp>

struct tcp_header {
    uint16_t src_port;
    uint16_t dest_port;
    uint32_t seq_num;
    uint32_t ack_num;
    uint8_t data_offset;
    uint8_t flags;
    uint16_t window;
    uint16_t checksum;
    uint16_t urgent;
    uint8_t payload[];
};

void tcp_receive(uint32_t src_ip, uint32_t dest_ip, uint8_t* data, uint16_t len);
void tcp_send_syn(uint32_t dest_ip, uint16_t src_port, uint16_t dest_port);

#endif 