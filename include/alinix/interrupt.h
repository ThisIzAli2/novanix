/**
 * @author Ali Mirmohammad
 * @file interrupt.h
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
 * 	- Defines interrupts and IRQ.
*/

#ifndef __ALINIX_KERNEL_INTERRUPT_H
#define __ALINIX_KERNEL_INTERRUPT_H

#include <alinix/irqreturn.h>



enum irqchip_irq_state {
	IRQCHIP_STATE_PENDING,		/* Is interrupt pending? */
	IRQCHIP_STATE_ACTIVE,		/* Is interrupt in progress? */
	IRQCHIP_STATE_MASKED,		/* Is interrupt masked? */
	IRQCHIP_STATE_LINE_LEVEL,	/* Is IRQ line high? */
};
typedef enum irqreturn irqreturn_t;

typedef irqreturn_t (*irq_handler_t)(int, void *);

struct irqaction {
	irq_handler_t		handler;
	void			*dev_id;
	void 	*percpu_dev_id;
	struct irqaction	*next;
	irq_handler_t		thread_fn;
	// struct task_struct	*thread;
	struct irqaction	*secondary;
	unsigned int		irq;
	unsigned int		flags;
	unsigned long		thread_flags;
	unsigned long		thread_mask;
	const char		*name;
	// struct proc_dir_entry	*dir;
} ;



#endif // __ALINIX_KERNEL_INTERRUPT_H