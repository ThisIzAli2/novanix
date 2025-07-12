#ifndef __NOVANIX_KERNEL_WIFI_H
#define __NOVANIX_KERNEL_WIFI_H


#include <common/init.hpp>

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
        kprint(VGA_COLOR_WHITE,out,0);
        if (i != 5) kprint(VGA_COLOR_WHITE,":",0);
    }
    kprint(VGA_COLOR_WHITE,"\n",1);
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

// Simulate reading a frame from hardware (fake beacon frame)
int read_frame_from_hardware(uint8_t *buffer) {
    static int called = 0;
    if (called++) return 0;

    uint8_t fake_beacon[] = {
        0x80, 0x00,                         // Frame Control (beacon)
        0x00, 0x00,                         // Duration
        0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, // Destination (broadcast)
        0xDE, 0xAD, 0xBE, 0xEF, 0xAA, 0xBB, // Source
        0xDE, 0xAD, 0xBE, 0xEF, 0xAA, 0xBB, // BSSID (AP MAC)
        0x00, 0x00,                         // Sequence
        // Fixed Params (timestamp, interval, capabilities)
        0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
        0x64, 0x00,
        0x11, 0x04,
        // Tagged Parameters
        0x00, 0x06,                         // Tag: SSID, length 6
        'N', 'O', 'V', 'A', 'O', 'S'
    };

    int len = sizeof(fake_beacon);
    for (int i = 0; i < len; i++) {
        buffer[i] = fake_beacon[i];
    }
    return len;
}

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

                // Parse SSID tag (starts at offset 36 + 1 = 37)
                uint8_t ssid_len = frame_buffer[37];
                if (ssid_len > 31) ssid_len = 31;
                for (int s = 0; s < ssid_len; s++)
                    found_aps[ap_count].ssid[s] = frame_buffer[38 + s];
                found_aps[ap_count].ssid[ssid_len] = 0;

                ap_count++;
            }
        }
    }

    kprint(VGA_COLOR_WHITE,"Access Points Found:\n",1);
    for (int i = 0; i < ap_count; i++) {
        kprint(VGA_COLOR_WHITE,"SSID: ",0);
        kprint(VGA_COLOR_WHITE,found_aps[i].ssid,0);
        kprint(VGA_COLOR_WHITE," | MAC: ",0);
        print_mac(found_aps[i].mac);
    }
}

// Kernel main entry
void kernel_main() {
    kprint(VGA_COLOR_WHITE,"Starting WiFi scan...\n",1);
    scan_wifi_mac_addresses();
}



#endif /*__NOVANIX_KERNEL_WIFI_H*/