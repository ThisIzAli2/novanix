#ifndef __ipv4_h
#define __ipv4_h



#include <common/types.h>

using namespace Novanix::common;



struct ipv4_header {
    uint8_t  version_ihl;
    uint8_t  tos;
    uint16_t total_length;
    uint16_t id;
    uint16_t flags_fragment_offset;
    uint8_t  ttl;
    uint8_t  protocol; // 1 = ICMP
    uint16_t checksum;
    uint32_t src_ip;
    uint32_t dst_ip;
};


#endif // __ipv4_h
