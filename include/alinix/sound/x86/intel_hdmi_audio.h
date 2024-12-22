/**
 * @file intel_hdmi_audio.h
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
 * 	- Kernel Audio file implementation.
*/
#ifndef __ALINIX_KERNEL_INTEL_HDMI_SOUND_AUDIO_H
#define __ALINIX_KERNEL_INTEL_HDMI_SOUND_AUDIO_H

#include <alinix/types.h>
#include <alinix/device.h>

#define MAX_PB_STREAMS		1
#define MAX_CAP_STREAMS		0
#define BYTES_PER_WORD		0x4
#define INTEL_HAD		"HdmiLpeAudio"


enum cea_speaker_placement {
	FL  = (1 <<  0),        /* Front Left           */
	FC  = (1 <<  1),        /* Front Center         */
	FR  = (1 <<  2),        /* Front Right          */
	FLC = (1 <<  3),        /* Front Left Center    */
	FRC = (1 <<  4),        /* Front Right Center   */
	RL  = (1 <<  5),        /* Rear Left            */
	RC  = (1 <<  6),        /* Rear Center          */
	RR  = (1 <<  7),        /* Rear Right           */
	RLC = (1 <<  8),        /* Rear Left Center     */
	RRC = (1 <<  9),        /* Rear Right Center    */
	LFE = (1 << 10),        /* Low Frequency Effect */
};

struct cea_channel_speaker_allocation{
	int ca_index;
	int speakers[8];

	/* derived values, just for convenience */
	int channels;
	int spk_mask;
};

struct channel_map_table {
    unsigned char map;
    unsigned char cea_slot;
    int spk_mask;
};


struct snd_intelhad_card{
    struct device *dev;
    int irq;
    void  *mmio_start;
	int num_pipes;
	int num_ports;
	// struct snd_intelhad pcm_ctx[3]; /* one for each port */
};



#endif // __ALINIX_KERNEL_INTEL_HDMI_SOUND_AUDIO_H