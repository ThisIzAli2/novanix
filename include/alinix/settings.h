/**
 * @author Ali Mirmohammad
 * @file settings.h
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
 * 	- Kernel settings implementations in the header file.
*/
#ifndef __ALINIX_KERNEL_SETTINGS_H
#define __ALINIX_KERNEL_SETTINGS_H


#include <alinix/irqdesc.h>
#include <alinix/irq.h>

#define IRQ_DEFAULT_INIT_FLAGS	0
/**
 * @brief IRQ settings.
*/
enum {
	_IRQ_DEFAULT_INIT_FLAGS	= IRQ_DEFAULT_INIT_FLAGS,
	_IRQ_PER_CPU		= IRQ_PER_CPU,
	_IRQ_LEVEL		= IRQ_LEVEL,
	_IRQ_NOPROBE		= IRQ_NOPROBE,
	_IRQ_NOREQUEST		= IRQ_NOREQUEST,
	_IRQ_NOTHREAD		= IRQ_NOTHREAD,
	_IRQ_NOAUTOEN		= IRQ_NOAUTOEN,
	_IRQ_MOVE_PCNTXT	= IRQ_MOVE_PCNTXT,
	_IRQ_NO_BALANCING	= IRQ_NO_BALANCING,
	_IRQ_NESTED_THREAD	= IRQ_NESTED_THREAD,
	_IRQ_PER_CPU_DEVID	= IRQ_PER_CPU_DEVID,
	_IRQ_IS_POLLED		= IRQ_IS_POLLED,
	_IRQ_DISABLE_UNLAZY	= IRQ_DISABLE_UNLAZY,
	_IRQ_HIDDEN		= IRQ_HIDDEN,
	_IRQ_NO_DEBUG		= IRQ_NO_DEBUG,
	_IRQF_MODIFY_MASK	= IRQF_MODIFY_MASK,
};


/**
 * irq_settings_is_per_cpu_devid - Check if IRQ descriptor has a per-CPU device ID
 * @desc: Pointer to the irq_desc structure representing the interrupt descriptor
 *
 * This function checks the status of the given interrupt descriptor to determine
 * if it has been set to use a per-CPU device ID. It examines the `status_use_accessors`
 * field of the `irq_desc` structure and returns true if the `_IRQ_PER_CPU_DEVID` flag
 * is set, otherwise it returns false.
 *
 * Return: true if the IRQ descriptor has a per-CPU device ID, false otherwise.
 */
static inline bool irq_settings_is_per_cpu_devid(struct irq_desc *desc)
{
	return desc->status_use_accessors & _IRQ_PER_CPU_DEVID;
}



#endif /*__ALINIX_KERNEL_SETTINGS_H*/