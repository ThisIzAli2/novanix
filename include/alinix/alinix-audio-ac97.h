/**
 * @author Ali Mirmohammad
 * @file alinix-audio-ac97.h
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
 *  - Alinix kernel Audio driver.
*/
#ifndef __AUDIO_C_97_H
#define __AUDIO_C_97_H


#define AC97_VENDOR_ID_REGISTER 0x00
#define AC97_RESET_REGISTER 0x00
#define AC97_MASTER_VOLUME_REGISTER 0x02
#define AC97_PCM_OUT_VOLUME_REGISTER 0x18


#include <alinix/port.h>
#include <alinix/types.h>
#include <alinix/module.h>


/**
 * @brief 
 * ac97 device structure.
*/
struct ac97_codec{
    uint32_t base_address;
    uint32_t irq;
    bool initialized;
} ac97_codec_t;

/**
 * @brief Starts the ac97 audio driver.
*/
VOID ac97_initialize();

#endif /*__AUDIO_C_97_H*/