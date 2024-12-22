/**
 * @author Ali Mirmohammad
 * @file irqdesc.h
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
 * 	- Implements the IRQ header file for the kernel.
*/
#ifndef __ALINIX_KERNEL_IRQ_DESC_H
#define __ALINIX_KERNEL_IRQ_DESC_H

#include <alinix/mutex_types.h>
#include <alinix/interrupt.h>
#include <alinix/irq.h>
#include <alinix/types.h>
#include <alinix/cpu_mask.h>
#include <alinix/wait.h>



/**
 * @brief IRQ desc structure.
*/
struct irq_desc {
	struct irq_common_data	irq_common_data;
	struct irq_data		irq_data;
	unsigned int	*kstat_irqs;
	// irq_flow_handler_t	handle_irq;
	struct irqaction	*action;	/* IRQ action list */
	unsigned int		status_use_accessors;
	unsigned int		core_internal_state__do_not_mess_with_it;
	unsigned int		depth;		/* nested irq disables */
	unsigned int		wake_depth;	/* nested wake enables */
	unsigned int		tot_count;
	unsigned int		irq_count;	/* For detecting broken IRQs */
	unsigned long		last_unhandled;	/* Aging timer for unhandled count */
	unsigned int		irqs_unhandled;
	atomic_t		threads_handled;
	int			threads_handled_last;
	raw_spinlock_t		lock;
	struct cpumask		*percpu_enabled;
	const struct cpumask	*percpu_affinity;
#ifdef CONFIG_SMP
	const struct cpumask	*affinity_hint;
	struct irq_affinity_notify *affinity_notify;
#ifdef CONFIG_GENERIC_PENDING_IRQ
	cpumask_var_t		pending_mask;
#endif /*CONFIG_GENERIC_PENDING_IRQ*/
#endif /*CONFIG_SMP*/
	unsigned long		threads_oneshot;
	atomic_t		threads_active;
	wait_queue_head_t       wait_for_threads;
#ifdef CONFIG_PM_SLEEP
	unsigned int		nr_actions;
	unsigned int		no_suspend_depth;
	unsigned int		cond_suspend_depth;
	unsigned int		force_resume_depth;
#endif /*CONFIG_PM_SLEEP*/
#ifdef CONFIG_PROC_FS
	struct proc_dir_entry	*dir;
#endif /*CONFIG_PROC_FS*/
#ifdef CONFIG_GENERIC_IRQ_DEBUGFS
	struct dentry		*debugfs_file;
	const char		*dev_name;
#endif /*CONFIG_GENERIC_IRQ_DEBUGFS*/
#ifdef CONFIG_SPARSE_IRQ
	struct rcu_head		rcu;
	struct kobject		kobj;
#endif /*CONFIG_SPARSE_IRQ*/
	struct mutex		request_mutex;
	int			parent_irq;
	struct module		*owner;
	const char		*name;
#ifdef CONFIG_HARDIRQS_SW_RESEND
	struct hlist_node	resend_node;
#endif /*CONFIG_HARDIRQS_SW_RESEND*/
};

extern struct irq_desc *irq_to_desc(unsigned int irq);


#endif /*__ALINIX_KERNEL_IRQ_DESC_H*/