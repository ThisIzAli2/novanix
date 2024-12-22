/**
 * @file pd.h
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
 * 	- Kernel USB header file util.
*/
#ifndef __ALINIX_KERNEL_USB_PD_H
#define __ALINIX_KERNEL_USB_PD_H

#ifdef __cplusplus
extern "C" {
#endif /*__cplusplus*/


#include <alinix/types.h>

/**
 * @ref https://github.com/torvalds/linux/blob/master/include/linux/usb/pd.h
*/
///////////////////////////////
/* USB PD Messages */
enum pd_ctrl_msg_type {
	/* 0 Reserved */
	PD_CTRL_GOOD_CRC = 1,
	PD_CTRL_GOTO_MIN = 2,
	PD_CTRL_ACCEPT = 3,
	PD_CTRL_REJECT = 4,
	PD_CTRL_PING = 5,
	PD_CTRL_PS_RDY = 6,
	PD_CTRL_GET_SOURCE_CAP = 7,
	PD_CTRL_GET_SINK_CAP = 8,
	PD_CTRL_DR_SWAP = 9,
	PD_CTRL_PR_SWAP = 10,
	PD_CTRL_VCONN_SWAP = 11,
	PD_CTRL_WAIT = 12,
	PD_CTRL_SOFT_RESET = 13,
	/* 14-15 Reserved */
	PD_CTRL_NOT_SUPP = 16,
	PD_CTRL_GET_SOURCE_CAP_EXT = 17,
	PD_CTRL_GET_STATUS = 18,
	PD_CTRL_FR_SWAP = 19,
	PD_CTRL_GET_PPS_STATUS = 20,
	PD_CTRL_GET_COUNTRY_CODES = 21,
	/* 22-31 Reserved */
};

enum pd_data_msg_type {
	/* 0 Reserved */
	PD_DATA_SOURCE_CAP = 1,
	PD_DATA_REQUEST = 2,
	PD_DATA_BIST = 3,
	PD_DATA_SINK_CAP = 4,
	PD_DATA_BATT_STATUS = 5,
	PD_DATA_ALERT = 6,
	PD_DATA_GET_COUNTRY_INFO = 7,
	PD_DATA_ENTER_USB = 8,
	/* 9-14 Reserved */
	PD_DATA_VENDOR_DEF = 15,
	/* 16-31 Reserved */
};

enum pd_ext_msg_type {
	/* 0 Reserved */
	PD_EXT_SOURCE_CAP_EXT = 1,
	PD_EXT_STATUS = 2,
	PD_EXT_GET_BATT_CAP = 3,
	PD_EXT_GET_BATT_STATUS = 4,
	PD_EXT_BATT_CAP = 5,
	PD_EXT_GET_MANUFACTURER_INFO = 6,
	PD_EXT_MANUFACTURER_INFO = 7,
	PD_EXT_SECURITY_REQUEST = 8,
	PD_EXT_SECURITY_RESPONSE = 9,
	PD_EXT_FW_UPDATE_REQUEST = 10,
	PD_EXT_FW_UPDATE_RESPONSE = 11,
	PD_EXT_PPS_STATUS = 12,
	PD_EXT_COUNTRY_INFO = 13,
	PD_EXT_COUNTRY_CODES = 14,
	/* 15-31 Reserved */
};

#define PD_REV10	0x0
#define PD_REV20	0x1
#define PD_REV30	0x2
#define PD_MAX_REV	PD_REV30

#define PD_HEADER_EXT_HDR	BIT(15)
#define PD_HEADER_CNT_SHIFT	12
#define PD_HEADER_CNT_MASK	0x7
#define PD_HEADER_ID_SHIFT	9
#define PD_HEADER_ID_MASK	0x7
#define PD_HEADER_PWR_ROLE	BIT(8)
#define PD_HEADER_REV_SHIFT	6
#define PD_HEADER_REV_MASK	0x3
#define PD_HEADER_DATA_ROLE	BIT(5)
#define PD_HEADER_TYPE_SHIFT	0
#define PD_HEADER_TYPE_MASK	0x1f

#define PD_HEADER(type, pwr, data, rev, id, cnt, ext_hdr)		\
	((((type) & PD_HEADER_TYPE_MASK) << PD_HEADER_TYPE_SHIFT) |	\
	 ((pwr) == TYPEC_SOURCE ? PD_HEADER_PWR_ROLE : 0) |		\
	 ((data) == TYPEC_HOST ? PD_HEADER_DATA_ROLE : 0) |		\
	 (rev << PD_HEADER_REV_SHIFT) |					\
	 (((id) & PD_HEADER_ID_MASK) << PD_HEADER_ID_SHIFT) |		\
	 (((cnt) & PD_HEADER_CNT_MASK) << PD_HEADER_CNT_SHIFT) |	\
	 ((ext_hdr) ? PD_HEADER_EXT_HDR : 0))


#define PD_HEADER_LE(type,pwr,data,rev,id,cnt) \
        cpu_to_le16(PD_HEADER((type), (pwr), (data), (rev), (id), (cnt), (0)))


PRIVATE __always_inline int pd_header_cnt(uint16_t header){
    return (header >> PD_HEADER_CNT_SHIFT) & PD_HEADER_CNT_MASK;
}


///////////////////////////////
#ifdef __cplusplus
}
#endif /*__cplusplus*/

#endif /*__ALINIX_KERNEL_USB_PD_H*/