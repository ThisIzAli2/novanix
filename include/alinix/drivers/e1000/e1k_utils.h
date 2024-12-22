/**
 * @file e1k_utils.h
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
 * @abstract:
 * 	- e1k Utils header file implementation.
*/

#ifndef __ALINIX_KERNEL_E1L_DRIVERS_NET_UTILS_H
#define __ALINIX_KERNEL_E1L_DRIVERS_NET_UTILS_H

#include <alinix/types.h>


#define E1K_MAX_TX_PKT_SIZE 16288

/* ---------------------------- Register Offset	--------------------------- */
#define CTRL			0x00000		/* Device Control					RW	*/
#define STATUS			0x00008		/* Device Status					RO	*/
#define EECD			0x00010		/* EEPROM/Flash Control				RW	*/
#define RCTL			0x00100		/* RX Control						RW	*/
#define TCTL			0x00400		/* TX Control						RW	*/
#define TDBAL			0x03800		/* TX Descriptor Base Address Low	RW	*/
#define TDBAH			0x03804		/* TX Descriptor Base Address High	RW	*/
#define TDLEN			0x03808		/* TX Descriptor Length				RW	*/
#define TDH				0x03810		/* TX Descriptor Head				RW	*/
#define TDT				0x03818		/* TX Descripotr Tail				RW	*/

/* ------------------------ CTRL Register Bits Masks ---------------------- */
#define CTRL_FD			0x00000001	/* Full duplex.0=half; 1=full			*/
#define CTRL_ASDE		0x00000020	/* Auto-speed detect enable				*/
#define CTRL_SLU		0x00000040	/* Set link up (Force Link)				*/
#define CTRL_RST		0x04000000	/* Global reset							*/

/* ------------------------ EECD Register Bits Masks ---------------------- */
#define EECD_SK			0x00000001	/* EEPROM Clock							*/
#define EECD_CS			0x00000002	/* EEPROM Chip Select					*/
#define EECD_DI			0x00000004	/* EEPROM Data In						*/
#define EECD_DO			0x00000008	/* EEPROM Data Out						*/
#define EECD_FWE_EN 	0x00000020  /* Enable FLASH writes					*/
#define EECD_REQ		0x00000040	/* EEPROM Access Request				*/
#define EECD_GNT		0x00000080	/* EEPROM Access Grant					*/

/* ------------------------ RCTL Register Bits Masks ---------------------- */
#define RCTL_LBM_NO		0x00000000	/* No loopback mode						*/
#define RCTL_LBM_TCVR	0x000000C0	/* TCVR loopback mode					*/

/* ------------------------ TCTL Register Bits Masks ---------------------- */
#define TCTL_EN			0x00000002	/* Enable tx							*/
#define TCTL_PSP		0x00000008	/* Pad short packets					*/
#define TCTL_CT			0x00000ff0	/* Collision threshold					*/
#define TCTL_COLD		0x003ff000	/* Collision distance					*/
#define TCTL_RTLC		0x01000000	/* Re-transmit on late collision		*/

/* ---------------------------- Macro Function ---------------------------- */
#define write_iomem32(bar, reg, val)				\
		*(uint32_t*)(bar + reg) = (uint32_t) val
#define read_iomem32(bar, reg)						\
		({											\
				uint32_t val;						\
				val = *(uint32_t*)(bar + reg);		\
				val;								\
		})

#define get_register(reg)							\
		read_iomem32(bar0,reg)
#define set_register(reg,val)						\
		write_iomem32(bar0,reg,val)

#define low16(addr16)								\
		(uint8_t)(addr16 & 0xff)
#define high16(addr16)								\
		(uint8_t)((addr16 >> 8) & 0xff)
#define swap16(x)									\
		((((x) & 0xff) << 8) | (((x) & 0xff00) >> 8))


/* ----------------------- Offload Context Descriptor --------------------- */
#define TCP_IP			(3 << 24)
#define DESC_CTX		(1 << 29)
#define MSS_DEFAULT		(0x3010 << 16)
#define FIRST_PAYLEN	0x10
#define PAYLOAD_LEN		0x10000
#define STACK_LEN		0x4000

struct __attribute__((packed)) e1000_ctxt_desc {
	union {
		u32 ip_config;
		struct {
			uint8_t ipcss;			/* IP checksum start					*/
			uint8_t ipcso;			/* IP checksum offset					*/
			__le16 ipcse;			/* IP checksum end						*/
		} ip_fields;
	} lower_setup;
	union {
		u32 tcp_config;
		struct {
			uint8_t tucss;			/* TCP checksum start					*/
			uint8_t tucso;			/* TCP checksum offset					*/
			__le16 tucse;			/* TCP checksum end						*/
		} tcp_fields;
	} upper_setup;
	u32 cmd_and_length;			/*										*/
	union {
		u32 data;
		struct {
			uint8_t status;			/* Descriptor status					*/
			uint8_t hdr_len;		/* Header length						*/
			__le16 mss;				/* Maximum segment size 				*/
		} fields;
	} tcp_seg_setup;
};

#define DESC_DATA	((1 << 20) | (1 << 29))
#define EOP			(1 << 24)

struct __attribute__((packed)) e1000_data_desc {
	u64 buffer_addr;				/* Descriptor's buffer address			*/
	union {
		u32 data;
		struct {
			__le16 length;			/* Data buffer length					*/
			uint8_t typ_len_ext;	/*										*/
			uint8_t cmd;			/*										*/
		} flags;
	} lower;
	union {
		u32 data;
		struct {
			uint8_t status;			/* Descriptor status					*/
			uint8_t popts;			/* Packet Options						*/
			__le16 special;			/*										*/
		} fields;
	} upper;
};

/* -----------------------			Descriptor		 ---------------------- */
#define DESC_SIZE 		16
#define REPORT_STATUS	(1 << 27)
#define DESC_DONE		1
#define TSE				(1 << 26)

struct __attribute__((packed)) e1000_desc {
	union {
		struct e1000_ctxt_desc ctxt;
		struct e1000_data_desc data;
	};
};

#endif /*__ALINIX_KERNEL_E1L_DRIVERS_NET_UTILS_H*/