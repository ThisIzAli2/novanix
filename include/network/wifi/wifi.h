#ifndef __NOVANIX_KERNEL_WIFI_H
#define __NOVANIX_KERNEL_WIFI_H

#include <common/init.hpp>

// === VGA Printing for Kernel ===
#ifndef kprint
#define kprint Novanix::system::printk
#endif

void print_mac(uint8_t *mac) {
    char hex[] = "0123456789ABCDEF";
    for (int i = 0; i < 6; i++) {
        char out[3];
        out[0] = hex[(mac[i] >> 4) & 0xF];
        out[1] = hex[mac[i] & 0xF];
        out[2] = 0;
        kprint(VGA_COLOR_WHITE, out, 0);
        if (i != 5) kprint(VGA_COLOR_WHITE, ":", 0);
    }
    kprint(VGA_COLOR_WHITE, "\n", 1);
}

#define MAX_APS 32
#define FRAME_BUFFER_SIZE 2048

typedef struct {
    uint8_t mac[6];  // BSSID
    char ssid[32];   // Network name
} access_point_t;

access_point_t found_aps[MAX_APS];
int ap_count = 0;
uint8_t frame_buffer[FRAME_BUFFER_SIZE];

// ===========================
// === PCI + Wi-Fi Access ===
// ===========================

#define PCI_CONFIG_ADDRESS 0xCF8
#define PCI_CONFIG_DATA    0xCFC

static inline void outl(uint16_t port, uint32_t val) {
    asm volatile ("outl %0, %1" : : "a"(val), "Nd"(port));
}
static inline uint32_t inl(uint16_t port) {
    uint32_t ret;
    asm volatile ("inl %1, %0" : "=a"(ret) : "Nd"(port));
    return ret;
}

uint32_t pci_config_read(uint8_t bus, uint8_t slot, uint8_t func, uint8_t offset) {
    uint32_t address =
        ((uint32_t)bus << 16) | ((uint32_t)slot << 11) |
        ((uint32_t)func << 8) | (offset & 0xfc) | ((uint32_t)0x80000000);
    outl(PCI_CONFIG_ADDRESS, address);
    return inl(PCI_CONFIG_DATA);
}

uint32_t get_mmio_base(uint8_t bus, uint8_t slot, uint8_t func) {
    return pci_config_read(bus, slot, func, 0x10) & ~0xF;
}

// ===========================
// === Frame Reader (Real) ===
// ===========================
int read_frame_from_hardware(uint8_t *buffer) {
    // Replace below with real implementation for your chipset
    // This scaffolds access to PCI-based NIC MMIO

    // Example: Looking for Intel Wi-Fi 3945ABG (Vendor 0x8086, Device 0x4222)
    for (uint8_t bus = 0; bus < 256; bus++) {
        for (uint8_t slot = 0; slot < 32; slot++) {
            uint32_t vendor_device = pci_config_read(bus, slot, 0, 0x00);
            uint16_t vendor = vendor_device & 0xFFFF;
            uint16_t device = (vendor_device >> 16) & 0xFFFF;

            if (vendor == 0x8086) {
                kprint(VGA_COLOR_WHITE, "Intel device found\n", 1);

                uint32_t mmio_base = get_mmio_base(bus, slot, 0);
                kprint(VGA_COLOR_WHITE, "MMIO base: ", 0);
                // print as hex here if you wish

                volatile uint8_t* mmio = (volatile uint8_t*) mmio_base;

                // === Placeholder ===
                // Here you would:
                // 1. Initialize the card
                // 2. Set monitor mode
                // 3. Poll RX ring buffer
                // 4. Copy frame into `buffer`

                // Until implemented:
                return 0;
            }
        }
    }

    return 0;
}

// ===========================
// === Wi-Fi Scanner Logic ===
// ===========================

void scan_wifi_mac_addresses() {
    for (int i = 0; i < 1000; i++) {
        int size = read_frame_from_hardware(frame_buffer);
        if (size <= 0) continue;
        if (size < 36) continue;

        uint8_t frame_type = frame_buffer[0] & 0b00001100;
        uint8_t frame_subtype = frame_buffer[0] & 0b11110000;

        if (frame_type == 0x00 && frame_subtype == 0x80) {  // Beacon
            uint8_t *bssid = &frame_buffer[16];

            // Check for duplicates
            int duplicate = 0;
            for (int j = 0; j < ap_count; j++) {
                int match = 1;
                for (int k = 0; k < 6; k++) {
                    if (found_aps[j].mac[k] != bssid[k]) {
                        match = 0;
                        break;
                    }
                }
                if (match) {
                    duplicate = 1;
                    break;
                }
            }

            if (!duplicate && ap_count < MAX_APS) {
                for (int b = 0; b < 6; b++)
                    found_aps[ap_count].mac[b] = bssid[b];

                // Parse SSID tag
                uint8_t ssid_len = frame_buffer[37];
                if (ssid_len > 31) ssid_len = 31;
                for (int s = 0; s < ssid_len; s++)
                    found_aps[ap_count].ssid[s] = frame_buffer[38 + s];
                found_aps[ap_count].ssid[ssid_len] = 0;

                ap_count++;
            }
        }
    }

    kprint(VGA_COLOR_WHITE, "Access Points Found:\n", 1);
    for (int i = 0; i < ap_count; i++) {
        kprint(VGA_COLOR_WHITE, "SSID: ", 0);
        kprint(VGA_COLOR_WHITE, found_aps[i].ssid, 0);
        kprint(VGA_COLOR_WHITE, " | MAC: ", 0);
        print_mac(found_aps[i].mac);
    }
}

// ===========================
// === Kernel Entry Point ====
// ===========================
void kernel_main() {
    kprint(VGA_COLOR_WHITE, "Starting WiFi scan...\n", 1);
    scan_wifi_mac_addresses();
}

#endif /* __NOVANIX_KERNEL_WIFI_H */
