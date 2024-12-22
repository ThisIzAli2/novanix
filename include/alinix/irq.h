/**
 * @author Ali Mirmohammad
 * @file irq.h
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
 * 	- IRQ utils defined.
 * 	- Function implementation for IRQ.
*/
#ifndef __ALINIX_KERNEL_IRQ_H
#define __ALINIX_KERNEL_IRQ_H

#include <alinix/types.h>
#include <alinix/interrupt.h>
#include <alinix/cpu.h>


/**
 * @brief IRQ data structure.
*/
struct irq_data {
	u32			mask;
	unsigned int		irq;
	irq_hw_number_t		hwirq;
	struct irq_common_data	*common;
	struct irq_chip		*chip;
	struct irq_domain	*domain;
#ifdef	CONFIG_IRQ_DOMAIN_HIERARCHY
	struct irq_data		*parent_data;
#endif /*CONFIG_IRQ_DOMAIN_HIERARCHY*/
	void			*chip_data;
};

enum {
	/** No specific IRQ type */
	IRQ_TYPE_NONE		= 0x00000000,
	/** IRQ triggered on a rising edge */
	IRQ_TYPE_EDGE_RISING	= 0x00000001,
	/** IRQ triggered on a falling edge */
	IRQ_TYPE_EDGE_FALLING	= 0x00000002,
	/** IRQ triggered on both rising and falling edges */
	IRQ_TYPE_EDGE_BOTH	= (IRQ_TYPE_EDGE_FALLING | IRQ_TYPE_EDGE_RISING),
	/** IRQ triggered when the level is high */
	IRQ_TYPE_LEVEL_HIGH	= 0x00000004,
	/** IRQ triggered when the level is low */
	IRQ_TYPE_LEVEL_LOW	= 0x00000008,
	/** Mask for level-triggered IRQ types */
	IRQ_TYPE_LEVEL_MASK	= (IRQ_TYPE_LEVEL_LOW | IRQ_TYPE_LEVEL_HIGH),
	IRQ_TYPE_SENSE_MASK	= 0x0000000f,
	/** Mask for all IRQ sense types */
	IRQ_TYPE_DEFAULT	= IRQ_TYPE_SENSE_MASK,
	/** Default IRQ sense type */
	IRQ_TYPE_PROBE		= 0x00000010,
	/** IRQ probe type */

	/** Level-triggered IRQ flag */
	IRQ_LEVEL		= (1 <<  8),
	/** IRQ is per-CPU */
	IRQ_PER_CPU		= (1 <<  9),
	IRQ_NOPROBE		= (1 << 10),
	IRQ_NOREQUEST		= (1 << 11),
	IRQ_NOAUTOEN		= (1 << 12),
	IRQ_NO_BALANCING	= (1 << 13),
	IRQ_MOVE_PCNTXT		= (1 << 14),
	IRQ_NESTED_THREAD	= (1 << 15),
	IRQ_NOTHREAD		= (1 << 16),
	IRQ_PER_CPU_DEVID	= (1 << 17),
	IRQ_IS_POLLED		= (1 << 18),
	IRQ_DISABLE_UNLAZY	= (1 << 19),
	IRQ_HIDDEN		= (1 << 20),
	IRQ_NO_DEBUG		= (1 << 21),
};

#define IRQF_MODIFY_MASK	\
	(IRQ_TYPE_SENSE_MASK | IRQ_NOPROBE | IRQ_NOREQUEST | \
	 IRQ_NOAUTOEN | IRQ_MOVE_PCNTXT | IRQ_LEVEL | IRQ_NO_BALANCING | \
	 IRQ_PER_CPU | IRQ_NESTED_THREAD | IRQ_NOTHREAD | IRQ_PER_CPU_DEVID | \
	 IRQ_IS_POLLED | IRQ_DISABLE_UNLAZY | IRQ_HIDDEN)


struct irq_common_data {
	unsigned int		 state_use_accessors;
#ifdef CONFIG_NUMA
	unsigned int		node;
#endif /*CONFIG_NUMA*/
	void			*handler_data;
	// struct msi_desc		*msi_desc;
#ifdef CONFIG_SMP
	cpumask_var_t		affinity;
#endif /*CONFIG_SMP*/
#ifdef CONFIG_GENERIC_IRQ_EFFECTIVE_AFF_MASK
	cpumask_var_t		effective_affinity;
#endif /*CONFIG_GENERIC_IRQ_EFFECTIVE_AFF_MASK*/
#ifdef CONFIG_GENERIC_IRQ_IPI
	unsigned int		ipi_offset;
#endif /*CONFIG_GENERIC_IRQ_IPI*/
};

struct irq_chip {
	const char	*name;
	unsigned int	(*irq_startup)(struct irq_data *data);
	void		(*irq_shutdown)(struct irq_data *data);
	void		(*irq_enable)(struct irq_data *data);
	void		(*irq_disable)(struct irq_data *data);

	void		(*irq_ack)(struct irq_data *data);
	void		(*irq_mask)(struct irq_data *data);
	void		(*irq_mask_ack)(struct irq_data *data);
	void		(*irq_unmask)(struct irq_data *data);
	void		(*irq_eoi)(struct irq_data *data);

	int		(*irq_set_affinity)(struct irq_data *data, const struct cpu *dest, bool force);
	int		(*irq_retrigger)(struct irq_data *data);
	int		(*irq_set_type)(struct irq_data *data, unsigned int flow_type);
	int		(*irq_set_wake)(struct irq_data *data, unsigned int on);

	void		(*irq_bus_lock)(struct irq_data *data);
	void		(*irq_bus_sync_unlock)(struct irq_data *data);

#ifdef CONFIG_DEPRECATED_IRQ_CPU_ONOFFLINE
	void		(*irq_cpu_online)(struct irq_data *data);
	void		(*irq_cpu_offline)(struct irq_data *data);
#endif /*CONFIG_DEPRECATED_IRQ_CPU_ONOFFLINE*/
	void		(*irq_suspend)(struct irq_data *data);
	void		(*irq_resume)(struct irq_data *data);
	void		(*irq_pm_shutdown)(struct irq_data *data);

	void		(*irq_calc_mask)(struct irq_data *data);

	void		(*irq_print_chip)(struct irq_data *data);
	int		(*irq_request_resources)(struct irq_data *data);
	void		(*irq_release_resources)(struct irq_data *data);

	void		(*irq_compose_msi_msg)(struct irq_data *data);
	void		(*irq_write_msi_msg)(struct irq_data *data);

	int		(*irq_get_irqchip_state)(struct irq_data *data, enum irqchip_irq_state which, bool *state);
	int		(*irq_set_irqchip_state)(struct irq_data *data, enum irqchip_irq_state which, bool state);

	int		(*irq_set_vcpu_affinity)(struct irq_data *data, void *vcpu_info);

	void		(*ipi_send_single)(struct irq_data *data, unsigned int cpu);
	void		(*ipi_send_mask)(struct irq_data *data, const struct cpu *dest);

	int		(*irq_nmi_setup)(struct irq_data *data);
	void		(*irq_nmi_teardown)(struct irq_data *data);

	unsigned long	flags;
};

#endif // __ALINIX_KERNEL_IRQ_H