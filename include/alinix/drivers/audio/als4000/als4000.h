/**
 * @file als4000.h
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
 * 	- Driver audio util.
*/
#ifndef __ALINIX_KERNEL_AUDIO_als4000_H
#define __ALINIX_KERNEL_AUDIO_als4000_H

#define EINIVAL 42

#include <alinix/types.h>

/* Subdevice type */
#define DAC		0
#define ADC		1
#define MIX		2

/* PCI number and driver name */
#define VENDOR_ID		0x4005
#define DEVICE_ID		0x4000
#define DRIVER_NAME		"ALS4000"

/* Volume option */
#define GET_VOL			0
#define SET_VOL			1

/* Interrupt control */
#define INTR_ENABLE		1
#define INTR_DISABLE	0

/* Interrupt status */
#define INTR_STS_DAC		0x80
#define INTR_STS_ADC		0x40

/* ======= Self-defined Parameter ======= */
#define REG_MIXER_ADDR		0x04
#define REG_MIXER_DATA		0x05
#define REG_GCR_DATA		0x08
#define REG_GCR_INDEX		0x0c
#define REG_INTR_STS		0x0e
#define REG_INTR_CTRL		0x8c
#define REG_DMA_EM_CTRL		0x99

#define REG_DAC_DMA_ADDR	0x91
#define REG_DAC_DMA_LEN		0x92
#define REG_DAC_CUR_ADDR	0xa0
#define REG_ADC_DMA_ADDR	0xa2
#define REG_ADC_DMA_LEN		0xa3
#define REG_ADC_CUR_ADDR	0xa4

#define REG_SB_CONFIG		0x00
#define REG_SB_RESET		0x06
#define REG_SB_READ			0x0a
#define REG_SB_CMD			0x0c
#define REG_SB_DATA			0x0e
#define REG_SB_BASE			0x10
#define REG_SB_FIFO_LEN_LO	0x1c
#define REG_SB_FIFO_LEN_HI	0x1d
#define REG_SB_FIFO_CTRL	0x1e
#define REG_SB_DMA_SETUP	0x81
#define REG_SB_IRQ_STATUS	0x82
#define REG_SB_CTRL			0xc0

#define CMD_MIXER_WRITE_ENABLE	0x80
#define CMD_SOUND_ON			0xd1
#define CMD_INTR_ENABLE			0x28000
#define CMD_SAMPLE_RATE_OUT		0x41
#define CMD_SIGN_MONO			0x10
#define CMD_SIGN_STEREO			0x30
#define CMD_UNSIGN_MONO			0x00
#define CMD_UNSIGN_STEREO		0x20
#define CMD_BIT16_AI			0xb6
#define CMD_BIT16_DMA_OFF		0xd5
#define CMD_BIT16_DMA_ON		0xd6
#define CMD_BIT8_AI				0xc6
#define CMD_BIT8_DMA_OFF		0xd0
#define CMD_BIT8_DMA_ON			0xd4

#define CMD_REC_WIDTH8			0x04
#define CMD_REC_STEREO			0x20
#define CMD_REC_SIGN			0x10

static uint32_t g_sample_rate[] = {
	5512, 11025, 22050, 44100, 8000, 16000, 32000, 48000
};

/* Driver Data Structure */
typedef struct aud_sub_dev_conf_t {
	uint32_t stereo;
	uint16_t sample_rate;
	uint32_t nr_of_bits;
	uint32_t sign;
	uint32_t busy;
	uint32_t fragment_size;
	uint8_t format;
} aud_sub_dev_conf_t;

typedef struct DEV_STRUCT {
	char *name;
	uint16_t vid;
	uint16_t did;
	uint32_t devind;
	uint32_t base[6];
	char irq;
	char revision;
	uint32_t intr_status;
} DEV_STRUCT;

void dev_mixer_write(uint32_t *base, uint32_t reg, uint32_t val);
uint32_t dev_mixer_read(uint32_t *base, uint32_t reg);



#endif /*__ALINIX_KERNEL_AUDIO_als4000_H*/
