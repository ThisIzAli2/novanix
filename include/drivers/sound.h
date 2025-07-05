#ifndef __NOVANIX_KERNEL_SOUND_H
#define __NOVANIX_KERNEL_SOUND_H


#include <common/types.h>
#include <drivers/ports.h>
#include <core/port.h>

using namespace Novanix::common;




inline void play_beep() {
    uint32_t freq = 1000; // Frequency in Hz

    uint16_t div = 1193180 / freq; // PIT input frequency is 1193180 Hz

    outb(0x43, 0xB6);             // Command byte
    outb(0x42, div & 0xFF);       // Low byte
    outb(0x42, div >> 8);         // High byte

    uint8_t tmp = inb(0x61);
    if (tmp != (tmp | 3)) {
        outb(0x61, tmp | 3);      // Enable speaker
    }
}

// Stop the beep
inline void stop_beep() {
    uint8_t tmp = inb(0x61) & 0xFC;  // Clear bits 0 and 1
    outb(0x61, tmp);                 // Disable speaker
}

#endif