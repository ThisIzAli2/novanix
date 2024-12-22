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
 *  - Kernel e1000 driver, nvm header file.
*/
#ifndef __ALINIX_KERNEL_DRIVERS_E_1000_NVM_H
#define __ALINIX_KERNEL_DRIVERS_E_1000_NVM_H

#include <alinix/types.h>
#include "hw.h"


void e1000_init_nvm_ops_generic(struct e1000_hw *hw);
sint32_t  e1000e_acquire_nvm(struct e1000_hw *hw);

sint32_t  e1000e_poll_eerd_eewr_done(struct e1000_hw *hw, int ee_reg);
sint32_t  e1000_read_mac_addr_generic(struct e1000_hw *hw);
sint32_t  e1000_read_pba_string_generic(struct e1000_hw *hw, u8 *pba_num,
                                   u32 pba_num_size);
sint32_t  e1000e_read_nvm_eerd(struct e1000_hw *hw, u16 offset, u16 words,
                         u16 *data);
sint32_t  e1000e_valid_led_default(struct e1000_hw *hw, u16 *data);
sint32_t  e1000e_validate_nvm_checksum_generic(struct e1000_hw *hw);
sint32_t  e1000e_write_nvm_spi(struct e1000_hw *hw, u16 offset, u16 words,
                         u16 *data);
sint32_t  e1000e_update_nvm_checksum_generic(struct e1000_hw *hw);
void e1000e_release_nvm(struct e1000_hw *hw);

#define E1000_STM_OPCODE  0xDB00


#endif /*__ALINIX_KERNEL_DRIVERS_E_1000_NVM_H*/