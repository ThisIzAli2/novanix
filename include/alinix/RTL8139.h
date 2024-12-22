/**
 * @author Ali Mirmohammad
 * @file RTL8139.h
 ** This file is part of AliNix.

**AliNix is free software: you can redistribute it and/or modify
**it under the terms of the GNU Affero General Public License as published by
**the Free Software Foundation, either version 3 of the License, or
**(at your option) any later version.

**AliNix is distributed in the hope that it will be useful,
**but WITHOUT ANY WARRANTY; without even the implied warranty of
**MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
**GNU Affero General Public License for more details.

**You should have received a copy of the GNU Affero General Public License
**along with AliNix. If not, see <https://www.gnu.org/licenses/>.
*/

/**
 * @abstraction:
 *  - Kernel RTL device driver header file implementations.
*/
#ifndef __ALINIX_KERNEL_RT_81_39_H  
#define __ALINIX_KERNEL_RT_81_39_H

#include <alinix/module.h>
#include <alinix/types.h>


/**
 * @brief Some useful macros for the networking device.
*/
#define TO_SUM_IO_ADDRESS 0x52
#define OUT_PORT_RTL_ADDRESS 0x0
#define SOFTWARE_RESET_IO_PORT 0x37
#define SOFTWARE_OUT_IO_PORT 0x10
#define IMR_PORT 0x3C
#define IMR_OUT_PORT 0x0005

#define TOK 0x4 // 0100 in binary, represents the 3rd bit
#define ROK 0x1 // 0001 in binary, represents the 1st bit


/**
 * @brief Space for PCI config as structure.
*/
struct pci_config_space{
    uint16_t vendor_id;
    uint16_t device_id;
    uint16_t command;
    uint16_t status;
    uint8_t revision_id;
    uint8_t prog_if;
    uint8_t subclass;
    uint8_t class_code;
    uint16_t version;
    uint8_t cache_line_size;
    uint8_t latency_timer;
    uint8_t header_type;
    uint8_t bist;
    struct mmio_s mmio;
    uint32_t bar[6]; // Base Address Registers
    uint32_t cardbus_cis;
    uint16_t subsys_vendor_id;
    uint16_t subsys_id;
    uint32_t expansion_rom_base;
    uint8_t capabilities_ptr;
    uint8_t reserved[7];
    uint8_t interrupt_line;
    uint8_t interrupt_pin;
    uint8_t min_grant;
    uint8_t max_latency;
    uint8_t ioaddr;
    uint16_t io_base;
};

// MAC Control Registers
struct mac_control_regs {
    uint32_t tx_status[4]; // Transmit status of the four Tx buffers
    uint32_t tx_addr[4];   // Addresses of the four Tx buffers
    uint32_t rx_buf;       // Receive buffer address
    uint32_t rx_early_cnt; // Early Rx byte count
    uint32_t rx_early_status; // Early Rx status
    uint16_t command;
    uint16_t intr_mask;    // Interrupt mask
    uint16_t intr_status;  // Interrupt status
    uint32_t tx_config;    // Transmit configuration
    uint32_t rx_config;    // Receive configuration
    uint32_t timer;        // Timer
    uint32_t rx_missed;    // Missed packet count
    uint32_t rx_overflow;  // Rx overflow
    uint32_t tx_underflow; // Tx underflow
    uint8_t mac_addr[6];   // MAC address
    uint8_t reserved[2];
};

// EEPROM Control Registers
struct eeprom_control_regs {
    uint32_t eeprom_cmd;   // EEPROM command
    uint32_t eeprom_data;  // EEPROM data
};

// DMA Control Registers
struct dma_control_regs {
    uint32_t dma_addr;     // DMA address
    uint32_t dma_len;      // DMA length
    uint32_t dma_cmd;      // DMA command
    uint32_t dma_status;   // DMA status
};

// RTL8139 Network Interface Controller
struct rtl8139 {
    struct pci_config_space pci_config;   // PCI configuration space
    struct mac_control_regs mac_ctrl;     // MAC control registers
    struct eeprom_control_regs eeprom_ctrl; // EEPROM control registers
    struct dma_control_regs dma_ctrl;     // DMA control registers
};


void rtl8139_interrupt(struct rtl8139 *dev);

void rtl8139_eoi(struct rtl8139 *dev);

void rtl8139_set_irq(int irq);

void rtl8139_clear_irq(int irq);

void rtl8139_handle_irq(int irq);

void rtl8139_handler(uint8_t isr, uint64_t error, uint64_t irq,struct rtl8139 *dev);

VOID init_rtl();

static struct pci_config_space *device;

#endif /*__ALINIX_KERNEL_RT_81_39_H*/

