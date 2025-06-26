#ifndef __ipv4_h
#define __ipv4_h


#include <common/init.hpp>
// ipv4.c
// Self-contained IPv4 + ICMP handler

#define ETHERTYPE_IPV4 0x0800
#define IPPROTO_ICMP   1

#define htons(x) __builtin_bswap16(x)
#define ntohs(x) __builtin_bswap16(x)
#define htonl(x) __builtin_bswap32(x)
#define ntohl(x) __builtin_bswap32(x)

typedef unsigned char  uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int   uint32_t;
typedef unsigned long  size_t;

#define NULL ((void*)0)

// Ethernet frame (14 bytes)
struct eth_frame {
    uint8_t  dst_mac[6];
    uint8_t  src_mac[6];
    uint16_t ethertype;
    uint8_t  payload[1500]; // payload includes IP
};

// IPv4 Header
struct ipv4_header {
    uint8_t  version_ihl;
    uint8_t  dscp_ecn;
    uint16_t total_length;
    uint16_t identification;
    uint16_t flags_fragment;
    uint8_t  ttl;
    uint8_t  protocol;
    uint16_t header_checksum;
    uint32_t src_ip;
    uint32_t dst_ip;
} __attribute__((packed));

// ICMP Header
struct icmp_header {
    uint8_t  type;
    uint8_t  code;
    uint16_t checksum;
    uint16_t id;
    uint16_t sequence;
    uint8_t  data[];
} __attribute__((packed));

// Replace with your kernel's MAC and IP
uint8_t  my_mac[6] = { 0x52, 0x54, 0x00, 0x12, 0x34, 0x56 };
uint32_t my_ip     = 0x0A00020F;  // 10.0.2.15 (in hex)

// -- Minimal memcpy_ip --
void *memcpy_ip(void *dest, const void *src, size_t n) {
    // // uint8_t *d = dest;
    // const uint8_t *s = src;
    // while (n--) *d++ = *s++;
    // return dest;
}

// -- IPv4 Checksum --
uint16_t ipv4_checksum(uint16_t *data, size_t len) {
    uint32_t sum = 0;
    for (; len > 1; len -= 2)
        sum += *data++;

    if (len == 1)
        sum += *(uint8_t *)data;

    while (sum >> 16)
        sum = (sum & 0xFFFF) + (sum >> 16);

    return ~sum;
}

// -- Fake send_ethernet_frame --
// Replace with real network card send code
void send_ethernet_frame(uint8_t *dst_mac, uint16_t ethertype, uint8_t *payload, size_t len) {
    // This is a stub.
    // Use your network card driver to send a full Ethernet frame.
}

// -- Send IPv4 Packet --
void send_ipv4(uint32_t dst_ip, uint8_t *dst_mac, uint8_t protocol, uint8_t *payload, uint16_t payload_len) {
    struct ipv4_header ip;
    ip.version_ihl = 0x45;  // IPv4, 5*4 = 20 bytes
    ip.dscp_ecn = 0;
    ip.total_length = htons(sizeof(struct ipv4_header) + payload_len);
    ip.identification = htons(0x1234);  // Example ID
    ip.flags_fragment = htons(0x4000);  // Don't fragment
    ip.ttl = 64;
    ip.protocol = protocol;
    ip.src_ip = htonl(my_ip);
    ip.dst_ip = htonl(dst_ip);
    ip.header_checksum = 0;
    ip.header_checksum = ipv4_checksum((uint16_t *)&ip, sizeof(ip));

    uint8_t buffer[1500];
    memcpy_ip(buffer, &ip, sizeof(ip));
    memcpy_ip(buffer + sizeof(ip), payload, payload_len);

    send_ethernet_frame(dst_mac, ETHERTYPE_IPV4, buffer, sizeof(ip) + payload_len);
}

// -- Handle ICMP Echo Request --
void handle_icmp(struct eth_frame *frame, struct ipv4_header *ip, struct icmp_header *icmp, size_t len) {
    if (icmp->type != 8) return;  // Only handle Echo Request

    uint8_t response[1500];
    size_t icmp_len = len - sizeof(struct ipv4_header);
    memcpy_ip(response + sizeof(struct ipv4_header), icmp, icmp_len);

    struct icmp_header *icmp_resp = (struct icmp_header *)(response + sizeof(struct ipv4_header));
    icmp_resp->type = 0;  // Echo Reply
    icmp_resp->checksum = 0;
    icmp_resp->checksum = ipv4_checksum((uint16_t *)icmp_resp, icmp_len);

    send_ipv4(ntohl(ip->src_ip), frame->src_mac, IPPROTO_ICMP,
              (uint8_t *)icmp_resp, icmp_len);
}

// -- Handle IPv4 Packet --
void handle_ipv4(struct eth_frame *frame) {
    struct ipv4_header *ip = (struct ipv4_header *)frame->payload;
    if (ntohl(ip->dst_ip) != my_ip) return;
    if (ip->protocol == IPPROTO_ICMP) {
        struct icmp_header *icmp = (struct icmp_header *)(frame->payload + sizeof(struct ipv4_header));
        handle_icmp(frame, ip, icmp, ntohs(ip->total_length));
    }
}

// -- Main handler called by your NIC when a packet is received --
void handle_packet(uint8_t *packet, size_t len) {
    struct eth_frame *frame = (struct eth_frame *)packet;
    uint16_t type = ntohs(frame->ethertype);
    if (type == ETHERTYPE_IPV4) {
        handle_ipv4(frame);
    }
    // You can add ARP or other handlers here
}


#endif // __ipv4_h
