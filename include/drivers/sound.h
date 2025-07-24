/**
 * @author Ali Mirmohammad
 * @file sound.h
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

#ifndef __NOVANIX_KERNEL_SOUND_H
#define __NOVANIX_KERNEL_SOUND_H


#include <common/types.h>
#include <drivers/ports.h>
#include <core/port.h>

using namespace Novanix::common;




inline VOID play_beep(uint32_t freq) {
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
inline VOID stop_beep() {
    uint8_t tmp = inb(0x61) & 0xFC;  // Clear bits 0 and 1
    outb(0x61, tmp);                 // Disable speaker
}

VOID play_sound(uint32_t frequency);

#endif /*__NOVANIX_KERNEL_SOUND_H*/