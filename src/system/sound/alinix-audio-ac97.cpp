/**
 * @file alinix-audio-ac97.cpp
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
#include <alinix/alinix-audio-ac97.h>
#include <alinix/kernel.h>
#include <alinix/init.h>
#include <alinix/types.h>
#include <alinix/pci.h>
#include <alinix/interrupt.h>
#include <core/port.h>
#include <system/log.h>



MODULE_AUTHOR("Ali Mirmohammad")
MODULE_DESCRIPTION("AC97 Audio Driver")
MODULE_LICENSE("AGPL-3.0")
MODULE_VERSION("1.0")


static inline void ac97_write_register(uint16_t reg,uint16_t value,struct ac97_codec* dev){
    CactusOS::core::outportw(dev->base_address + reg,value);
}

static inline uint16_t ac97_read_register(uint16_t reg,struct ac97_codec* dev){
    return CactusOS::core::inportw(dev->base_address + reg);
}


void ac97_initialize(){
    struct ac97_codec* ac97Dev;
    ac97_write_register(AC97_RESET_REGISTER, 0,ac97Dev);
    uint16_t vendor_id = ac97_read_register(AC97_VENDOR_ID_REGISTER,ac97Dev);

    if (vendor_id != 0xFFFF){
        ac97Dev->initialized = true;
    }
    else {
        ac97Dev->initialized = false;
    }
        // Set master volume to maximum
    ac97_write_register(AC97_MASTER_VOLUME_REGISTER, 0x0000,ac97Dev);
    ac97_write_register(AC97_PCM_OUT_VOLUME_REGISTER, 0x0000,ac97Dev);
    asm volatile("sti");

}
