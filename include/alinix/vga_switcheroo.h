/**
 * @author Ali Mirmohammad
 * @file vga_switcheroo.h
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
 * 	- Kernel VGA drivers added.
*/
#ifndef __ALINIX_KERNEL_VGA_SWITCH_HEROO_H
#define __ALINIX_KERNEL_VGA_SWITCH_HEROO_H

enum vga_switcheroo_client_id {
	VGA_SWITCHEROO_UNKNOWN_ID = 0x1000,
	VGA_SWITCHEROO_IGD = 0,
	VGA_SWITCHEROO_DIS,
	VGA_SWITCHEROO_MAX_CLIENTS,
};

struct vga_switcheroo_handler {
	int (*init)(void);
	int (*switchto)(enum vga_switcheroo_client_id id);
	int (*switch_ddc)(enum vga_switcheroo_client_id id);
	int (*power_state)(enum vga_switcheroo_client_id id,
			   enum vga_switcheroo_state state);
	enum vga_switcheroo_client_id (*get_client_id)(struct pci_dev *pdev);
};



struct vga_switcheroo_client_ops {
	void (*set_gpu_state)(struct pci_dev *dev, enum vga_switcheroo_state);
	void (*reprobe)(struct pci_dev *dev);
	bool (*can_switch)(struct pci_dev *dev);
	void (*gpu_bound)(struct pci_dev *dev, enum vga_switcheroo_client_id);
};


#endif /*__ALINIX_KERNEL_VGA_SWITCH_HEROO_H*/