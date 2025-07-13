/**
 * @author Ali Mirmohammad
 * @file e1000_driver.cpp
 ** This file is part of Novanix.

**Novanix is free software: you can redistribute it and/or modify
**it under the terms of the GNU Affero General Public License as published by
**the Free Software Foundation, either version 3 of the License, or
**(at your option) any later version.

**Novanix is distributed in the hope that it will be useful,
**but WITHOUT ANY WARRANTY; without even the implied warranty of
**MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
**GNU Affero General Public License for more details.

**You should have received a copy of the GNU Affero General Public License
**along with Novanix. If not, see <https://www.gnu.org/licenses/>.
*/
#include <network/drivers/e1000_driver.h>

volatile uint32_t* mmio_base;

static inline void mmio_write(uint32_t offset, uint32_t value) {
    *((volatile uint32_t *)((uintptr_t)mmio_base + offset)) = value;
}
static inline uint32_t mmio_read(uint32_t offset) {
    return *((volatile uint32_t *)((uintptr_t)mmio_base + offset));
}

// Initialize the Intel 82540EM Ethernet Controller
void e1000_init(uint32_t mmio_addr) {
    mmio_base = (volatile uint32_t*)(uintptr_t)mmio_addr;

    // Disable interrupts
    mmio_write(E1000_REG_IMS, 0);

    // Setup RX ring
    for (int i = 0; i < NUM_RX_DESC; i++) {
        rx_desc[i].addr = (uint64_t)(uintptr_t)rx_buf[i];
        rx_desc[i].status = 0;
    }

    mmio_write(E1000_REG_RDBAL, (uint32_t)(uintptr_t)rx_desc);
    mmio_write(E1000_REG_RDLEN, NUM_RX_DESC * sizeof(e1000_rx_desc));
    mmio_write(E1000_REG_RDH, 0);
    mmio_write(E1000_REG_RDT, NUM_RX_DESC - 1);

    // Enable Receiver
    mmio_write(E1000_REG_RCTL, 0x00000002 | 0x00000010); // EN | UPE

    // Setup TX ring
    for (int i = 0; i < NUM_TX_DESC; i++) {
        tx_desc[i].addr = (uint64_t)(uintptr_t)tx_buf[i];
        tx_desc[i].status = 0x1;
    }

    mmio_write(E1000_REG_TDBAL, (uint32_t)(uintptr_t)tx_desc);
    mmio_write(E1000_REG_TDLEN, NUM_TX_DESC * sizeof(e1000_tx_desc));
    mmio_write(E1000_REG_TDH, 0);
    mmio_write(E1000_REG_TDT, 0);

    // Enable Transmitter
    mmio_write(E1000_REG_TCTL, 0x00000002 | 0x00000008 | 0x00000010); // EN | PSP | CT
}

// Transmit a frame (MAC level)
void e1000_send_packet(uint8_t* data, uint16_t len) {
    uint32_t tdt = mmio_read(E1000_REG_TDT);
    if (!(tx_desc[tdt].status & 0x1)) return; // Not ready

    for (int i = 0; i < len; i++) tx_buf[tdt][i] = data[i];

    tx_desc[tdt].length = len;
    tx_desc[tdt].cmd = (1 << 0) | (1 << 3); // EOP | IFCS
    tx_desc[tdt].status = 0;

    mmio_write(E1000_REG_TDT, (tdt + 1) % NUM_TX_DESC);
}

// Receive packets (basic polling)
int e1000_poll_receive(uint8_t* out_buf) {
    static int index = 0;
    if (!(rx_desc[index].status & 0x1)) return 0; // No packet

    uint16_t len = rx_desc[index].length;
    for (int i = 0; i < len; i++) out_buf[i] = rx_buf[index][i];

    rx_desc[index].status = 0;
    mmio_write(E1000_REG_RDT, index);
    index = (index + 1) % NUM_RX_DESC;

    return len;
}