/**
 * @file pcm.h
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
 * 	- Kernel PCM sound driver header file.
*/
#ifndef __ALINIX_KERNEL_SOUND_PCM_H
#define __ALINIX_KERNEL_SOUND_PCM_H

#include <alinix/types.h>

#define _SNDRV_PCM_FMTBIT(fmt)		

#define SNDRV_PCM_FMTBIT_S8		_SNDRV_PCM_FMTBIT(S8)
#define SNDRV_PCM_FMTBIT_U8		_SNDRV_PCM_FMTBIT(U8)
#define SNDRV_PCM_FMTBIT_S16_LE		_SNDRV_PCM_FMTBIT(S16_LE)
#define SNDRV_PCM_FMTBIT_S16_BE		_SNDRV_PCM_FMTBIT(S16_BE)
#define SNDRV_PCM_FMTBIT_U16_LE		_SNDRV_PCM_FMTBIT(U16_LE)
#define SNDRV_PCM_FMTBIT_U16_BE		_SNDRV_PCM_FMTBIT(U16_BE)
#define SNDRV_PCM_FMTBIT_S24_LE		_SNDRV_PCM_FMTBIT(S24_LE)
#define SNDRV_PCM_FMTBIT_S24_BE		_SNDRV_PCM_FMTBIT(S24_BE)
#define SNDRV_PCM_FMTBIT_U24_LE		_SNDRV_PCM_FMTBIT(U24_LE)
#define SNDRV_PCM_FMTBIT_U24_BE		_SNDRV_PCM_FMTBIT(U24_BE)

#define SNDRV_PCM_RATE_5512		(1U<<0)		/* 5512Hz */
#define SNDRV_PCM_RATE_8000		(1U<<1)		/* 8000Hz */
#define SNDRV_PCM_RATE_11025		(1U<<2)		/* 11025Hz */
#define SNDRV_PCM_RATE_16000		(1U<<3)		/* 16000Hz */
#define SNDRV_PCM_RATE_22050		(1U<<4)		/* 22050Hz */
#define SNDRV_PCM_RATE_32000		(1U<<5)		/* 32000Hz */
#define SNDRV_PCM_RATE_44100		(1U<<6)		/* 44100Hz */
#define SNDRV_PCM_RATE_48000		(1U<<7)		/* 48000Hz */
#define SNDRV_PCM_RATE_64000		(1U<<8)		/* 64000Hz */
#define SNDRV_PCM_RATE_88200		(1U<<9)		/* 88200Hz */
#define SNDRV_PCM_RATE_96000		(1U<<10)	/* 96000Hz */
#define SNDRV_PCM_RATE_176400		(1U<<11)	/* 176400Hz */
#define SNDRV_PCM_RATE_192000		(1U<<12)	/* 192000Hz */
#define SNDRV_PCM_RATE_352800		(1U<<13)	/* 352800Hz */
#define SNDRV_PCM_RATE_384000		(1U<<14)	/* 384000Hz */

#define SNDRV_PCM_FMTBIT_S32_LE		_SNDRV_PCM_FMTBIT(S32_LE)


struct snd_pcm_hardware {
	unsigned int info;		/* SNDRV_PCM_INFO_* */
	u64 formats;			/* SNDRV_PCM_FMTBIT_* */
	u32 subformats;			/* for S32_LE, SNDRV_PCM_SUBFMTBIT_* */
	unsigned int rates;		/* SNDRV_PCM_RATE_* */
	unsigned int rate_min;		/* min rate */
	unsigned int rate_max;		/* max rate */
	unsigned int channels_min;	/* min channels */
	unsigned int channels_max;	/* max channels */
	size_t buffer_bytes_max;	/* max buffer size */
	size_t period_bytes_min;	/* min period size */
	size_t period_bytes_max;	/* max period size */
	unsigned int periods_min;	/* min # of periods */
	unsigned int periods_max;	/* max # of periods */
	size_t fifo_size;		/* fifo size in bytes */
};


#endif /*__ALINIX_KERNEL_SOUND_PCM_H*/