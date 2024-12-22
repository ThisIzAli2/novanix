/**
 * @author Ali Mirmohammad
 * @file pit.h
 * *************************************IMPORTANT ALINIX LICENSE TERM********************************************
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
 *  - Kernel PIT header file implemented.
 *  - Header file.
*/
#ifndef __ALINIX_KERNEL_PIT_HEADER_H
#define __ALINIX_KERNEL_PIT_HEADER_H


#define PIT_FREQUENCY 1000


#include <alinix/types.h>

// typedef struct {
//     volatile uint64_t timer_ticks;
//     uint32_t (*handle_interrupt)(uint32_t);
//     void (*sleep)(uint32_t);
//     void (*play_sound)(uint32_t);
//     void (*no_sound)();
//     void (*beep)();
//     void (*beep_freq)(uint32_t);
//     void (*beep_freq_duration)(uint32_t, uint32_t);
//     uint64_t (*ticks)();
// } PIT;

// // Function prototypes
// uint32_t PIT_handle_interrupt(uint32_t esp);
// void PIT_sleep(uint32_t ms);
// void PIT_play_sound(uint32_t nFrequence);
// void PIT_no_sound();
// void PIT_beep();
// void PIT_beep_freq(uint32_t freq);
// void PIT_beep_freq_duration(uint32_t freq, uint32_t duration);
// uint64_t PIT_ticks();

// // Initialize PIT instance
// PIT pit = {
//     .timer_ticks = 0,
//     .handle_interrupt = PIT_handle_interrupt,
//     .sleep = PIT_sleep,
//     .play_sound = PIT_play_sound,
//     .no_sound = PIT_no_sound,
//     .beep = PIT_beep,
//     .beep_freq = PIT_beep_freq,
//     .beep_freq_duration = PIT_beep_freq_duration,
//     .ticks = PIT_ticks
// };

// Implement the functions
inline uint32_t PIT_handle_interrupt(uint32_t esp) {
    // Implementation here
    return esp;
}


// PIT* PIT_init();
// uint32_t PIT_HandleInterrupt(PIT* pit, uint32_t esp);
// void PIT_Sleep(PIT* pit, uint32_t ms);
// void PIT_PlaySound(PIT* pit, uint32_t nFrequence);
// void PIT_NoSound(PIT* pit);
// void PIT_Beep(PIT* pit);
// void PIT_Beep_freq(PIT* pit, uint32_t freq);
// void PIT_Beep_freq_duration(PIT* pit, uint32_t freq, uint32_t duration);
// uint64_t PIT_Ticks(PIT* pit);

#endif /*__ALINIX_KERNEL_PIT_HEADER_H*/