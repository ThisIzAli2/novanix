#ifndef _HEISEN_IRQHANDLER_H
#define _HEISEN_IRQHANDLER_H

/*
 * Interrupt flow handler typedefs are defined here to avoid circular
 * include dependencies.
 */

struct irq_desc;

typedef	void (*irq_flow_handler_t)(struct irq_desc *desc);

#endif