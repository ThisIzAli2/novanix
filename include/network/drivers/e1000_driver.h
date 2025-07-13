#ifndef __E1000_DRIVER_H
#define __E1000_DRIVER_H

#include <common/init.hpp>



#define E1000_VENDOR_ID 0x8086
#define E1000_DEVICE_ID 0x100E
#define E1000_REG_CTRL   0x0000  // Device Control Register
#define E1000_REG_STATUS 0x0008  // Device Status Register
#define E1000_REG_EERD   0x0014  // EEPROM Read
#define E1000_REG_RDBAL  0x2800  // Receive Descriptor Base Low
#define E1000_REG_RDLEN  0x2808  // Receive Descriptor Length
#define E1000_REG_RDH    0x2810  // Receive Descriptor Head
#define E1000_REG_RDT    0x2818  // Receive Descriptor Tail
#define E1000_REG_IMS    0x00D0  // Interrupt Mask Set
#define E1000_REG_RCTL   0x0100  // Receive Control Register
#define E1000_REG_TCTL   0x0400  // Transmit Control Register
#define E1000_REG_TDBAL  0x3800  // Transmit Descriptor Base Low
#define E1000_REG_TDLEN  0x3808  // Transmit Descriptor Length
#define E1000_REG_TDH    0x3810  // Transmit Descriptor Head
#define E1000_REG_TDT    0x3818  // Transmit Descriptor Tail

#define NUM_RX_DESC  32
#define NUM_TX_DESC  8
#define ETH_FRAME_SIZE 1518

// PCI access
uint32_t pci_config_read(uint8_t bus, uint8_t slot, uint8_t func, uint8_t offset) {
    uint32_t address = (1U << 31) | ((bus << 16) | (slot << 11) |
                                     (func << 8) | (offset & 0xFC));
    outl(0xCF8, address);
    return inl(0xCFC);
}

// MMIO access
volatile uint32_t* mmio_base;

static inline void mmio_write(uint32_t offset, uint32_t value) {
    *((volatile uint32_t *)((uintptr_t)mmio_base + offset)) = value;
}
static inline uint32_t mmio_read(uint32_t offset) {
    return *((volatile uint32_t *)((uintptr_t)mmio_base + offset));
}

// Descriptor structs
typedef struct {
    uint64_t addr;
    uint16_t length;
    uint16_t checksum;
    uint8_t  status;
    uint8_t  errors;
    uint16_t special;
} __attribute__((packed)) e1000_rx_desc;

typedef struct {
    uint64_t addr;
    uint16_t length;
    uint8_t  cso;
    uint8_t  cmd;
    uint8_t  status;
    uint8_t  css;
    uint16_t special;
} __attribute__((packed)) e1000_tx_desc;

// Buffers and descriptors
static e1000_rx_desc rx_desc[NUM_RX_DESC];
static e1000_tx_desc tx_desc[NUM_TX_DESC];
static uint8_t rx_buf[NUM_RX_DESC][ETH_FRAME_SIZE];
static uint8_t tx_buf[NUM_TX_DESC][ETH_FRAME_SIZE];

// Initialize the Intel 82540EM Ethernet Controller
void e1000_init(uint32_t mmio_addr);
// Transmit a frame (MAC level)
void e1000_send_packet(uint8_t* data, uint16_t len);

// Receive packets (basic polling)
int e1000_poll_receive(uint8_t* out_buf);

#endif /*__E1000_DRIVER_H*/