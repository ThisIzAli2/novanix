#include <network/tcp.h>
#include <common/types.h>

using namespace Novanix::common;

void tcp_receive(uint32_t src_ip, uint32_t dest_ip, uint8_t* data, uint16_t len) {
    struct tcp_header* tcp = (struct tcp_header*)data;

    // Novanix::system::printk(VGA_COLOR_WHITE,"Rec TCP",1);

}