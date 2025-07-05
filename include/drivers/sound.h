#ifndef __NOVANIX_KERNEL_SOUND_H
#define __NOVANIX_KERNEL_SOUND_H


#include <common/types.h>
#include <drivers/ports.h>
#include <core/port.h>

using namespace Novanix::common;




inline void play_beep(uint32_t freq) {
    uint16_t divisor = 1193180 / freq;

    // Configure PIT channel 2
    outb(0x43, 0xB6); // Binary, mode 3 (square wave), LSB then MSB, channel 2
    outb(0x42, divisor & 0xFF);   // Low byte
    outb(0x42, (divisor >> 8));   // High byte

    // Enable speaker (set bits 0 and 1 on port 0x61)
    uint8_t tmp = inb(0x61);
    if (!(tmp & 3)) {
        outb(0x61, tmp | 3);
    }
}

// Stop the beep
inline void stop_beep() {
    uint8_t tmp = inb(0x61) & 0xFC;  // Clear bits 0 and 1
    outb(0x61, tmp);                 // Disable speaker
}

#endif