#include <network/ip.h>
#include <network/net.h>
#include <common/types.h>




using namespace Novanix::common;

VOID net_receive(uint8_t* data,uint16_t size){
    struct eth_frame* frame = (struct eth_frame*)data;
    uint16_t eth_type = (frame->type << 8) | (frame->type >> 8); // Swap endian

    if (eth_type == ETH_TYPE_IPV4) {
        ip_receive(frame->payload, size - sizeof(struct eth_frame));
    }
}


