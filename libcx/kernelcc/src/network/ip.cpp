#include <network/ip.h>
#include <common/types.h>
#include <network/tcp.h>
#include <network/udp.h>


using namespace Novanix::common;


void ip_receive(uint8_t* data, uint16_t size) {
    struct ipv4_header* ip = (struct ipv4_header*)data;

    uint8_t ihl = (ip->ver_ihl & 0x0F) * 4;
    uint16_t total_len = (ip->length >> 8) | (ip->length << 8);

    uint16_t payload_len = total_len - ihl;
    uint8_t* payload = ip->payload;

    if (ip->protocol == IP_PROTOCOL_UDP) {
        udp_receive(ip->src_ip, ip->dest_ip, payload, payload_len);
    } else if (ip->protocol == IP_PROTOCOL_TCP) {
        tcp_receive(ip->src_ip, ip->dest_ip, payload, payload_len);
    }
}