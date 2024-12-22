/**
 * @file trigger.h
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

#ifndef __ALINIX_IIO_TRIGGER_H
#define __ALINIX_IIO_TRIGGER_H


#include <alinix/types.h>
#include <alinix/mutex_types.h>
#include <alinix/device.h>
#include <alinix/irq.h>
#include <alinix/list.h>


#define CONFIG_IIO_CONSUMERS_PER_TRIGGER 32 /* Maximum number of consumers per trigger */

struct iio_subirq {
	bool enabled;
};

struct iio_dev;
struct iio_trigger;

struct iio_trigger_ops {
	int (*set_trigger_state)(struct iio_trigger *trig, bool state);
	void (*reenable)(struct iio_trigger *trig);
	int (*validate_device)(struct iio_trigger *trig,
			       struct iio_dev *indio_dev);
};

/**
 * struct iio_trigger - industrial I/O trigger device
 * @ops:		[DRIVER] operations structure
 * @owner:		[INTERN] owner of this driver module
 * @id:			[INTERN] unique id number
 * @name:		[DRIVER] unique name
 * @dev:		[DRIVER] associated device (if relevant)
 * @list:		[INTERN] used in maintenance of global trigger list
 * @alloc_list:		[DRIVER] used for driver specific trigger list
 * @use_count:		[INTERN] use count for the trigger.
 * @subirq_chip:	[INTERN] associate 'virtual' irq chip.
 * @subirq_base:	[INTERN] base number for irqs provided by trigger.
 * @subirqs:		[INTERN] information about the 'child' irqs.
 * @pool:		[INTERN] bitmap of irqs currently in use.
 * @pool_lock:		[INTERN] protection of the irq pool.
 * @attached_own_device:[INTERN] if we are using our own device as trigger,
 *			i.e. if we registered a poll function to the same
 *			device as the one providing the trigger.
 * @reenable_work:	[INTERN] work item used to ensure reenable can sleep.
 **/
struct iio_trigger {
	const struct iio_trigger_ops	*ops;
	struct module			*owner;
	int				id;
	const char			*name;
	struct device			dev;

	struct list_head		list;
	struct list_head		alloc_list;
	atomic_t			use_count;

	struct irq_chip			subirq_chip;
	int				subirq_base;

	struct iio_subirq subirqs[CONFIG_IIO_CONSUMERS_PER_TRIGGER];
	unsigned long pool[CONFIG_IIO_CONSUMERS_PER_TRIGGER];
	struct mutex			pool_lock;
	bool				attached_own_device;
	// struct work_struct		reenable_work;
};



#endif /*__ALINIX_IIO_TRIGGER_H*/