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



#endif /*__E1000_DRIVER_H*/