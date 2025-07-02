#include <network/udp.h>
#include <common/types.h>

using namespace Novanix::common;

void udp_receive(uint32_t src_ip, uint32_t dest_ip, uint8_t* data, uint16_t len) {
    struct udp_header* udp = (struct udp_header*)data;

    // Novanix::system::printk(VGA_COLOR_WHITE,"rec",1);
        // (src_ip >> 24) & 0xFF, (src_ip >> 16) & 0xFF,
        // (src_ip >> 8) & 0xFF, src_ip & 0xFF,
        // udp->src_port);
    
    // Handle payload...
}