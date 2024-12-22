/**
 * @file nvm.h
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
 * 	- e1000 driver.
*/

#ifndef __ALINIX_KERNEL_MANAGE_DRIVERS_E1000_H
#define __ALINIX_KERNEL_MANAGE_DRIVERS_E1000_H



#include <alinix/types.h>
#include "hw.h"

bool e1000e_check_mng_mode_generic(struct e1000_hw *hw);
bool e1000e_enable_tx_pkt_filtering(struct e1000_hw *hw);
sint32_t  e1000_mng_enable_host_if(struct e1000_hw *hw);
sint32_t  e1000_mng_host_if_write(struct e1000_hw *hw, u8 *buffer,
                                     u16 length, u16 offset, u8 *sum);
sint32_t  e1000_mng_write_cmd_header(struct e1000_hw *hw,
                                    struct e1000_host_mng_command_header *hdr);
sint32_t  e1000e_mng_write_dhcp_info(struct e1000_hw *hw,
                                       u8 *buffer, u16 length);
bool e1000e_enable_mng_pass_thru(struct e1000_hw *hw);

enum e1000_mng_mode {
	e1000_mng_mode_none = 0,
	e1000_mng_mode_asf,
	e1000_mng_mode_pt,
	e1000_mng_mode_ipmi,
	e1000_mng_mode_host_if_only
};

#define E1000_FACTPS_MNGCG    0x20000000

#define E1000_FWSM_MODE_MASK  0xE
#define E1000_FWSM_MODE_SHIFT 1

#define E1000_MNG_IAMT_MODE                  0x3
#define E1000_MNG_DHCP_COOKIE_LENGTH         0x10
#define E1000_MNG_DHCP_COOKIE_OFFSET         0x6F0
#define E1000_MNG_DHCP_COMMAND_TIMEOUT       10
#define E1000_MNG_DHCP_TX_PAYLOAD_CMD        64
#define E1000_MNG_DHCP_COOKIE_STATUS_PARSING 0x1
#define E1000_MNG_DHCP_COOKIE_STATUS_VLAN    0x2

#define E1000_VFTA_ENTRY_SHIFT               5
#define E1000_VFTA_ENTRY_MASK                0x7F
#define E1000_VFTA_ENTRY_BIT_SHIFT_MASK      0x1F

#define E1000_HI_MAX_BLOCK_BYTE_LENGTH       1792 /* Num of bytes in range */
#define E1000_HI_MAX_BLOCK_DWORD_LENGTH      448 /* Num of dwords in range */
#define E1000_HI_COMMAND_TIMEOUT             500 /* Process HI command limit */
#define E1000_HICR_EN              0x01  /* Enable bit - RO */
/* Driver sets this bit when done to put command in RAM */
#define E1000_HICR_C               0x02
#define E1000_HICR_SV              0x04  /* Status Validity */
#define E1000_HICR_FW_RESET_ENABLE 0x40
#define E1000_HICR_FW_RESET        0x80

/* Intel(R) Active Management Technology signature */
#define E1000_IAMT_SIGNATURE  0x544D4149

#endif /*__ALINIX_KERNEL_MANAGE_DRIVERS_E1000_H*/