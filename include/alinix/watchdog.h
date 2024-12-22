/**
 * @author Ali Mirmohammad
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
 * @file watchdog.h
 * @abstract:
 * 	- Watchdog implementation for the kernel.
*/
#ifndef __ALINIX_KERNEL_WATCH_DOG_H
#define __ALINIX_KERNEL_WATCH_DOG_H

#include <alinix/notifier.h>
#include <alinix/kconf.h>
#include <alinix/asm/fcntl.h>
#include <alinix/asm/bitops.h>
#include <alinix/kernel.h>

#define UINT_MAX	(~0U)

struct watchdog_ops;
struct watchdog_device;
struct watchdog_core_data;
struct watchdog_governor;


struct watchdog_ops {
	struct module *owner;
	/* mandatory operations */
	int (*start)(struct watchdog_device *);
	/* optional operations */
	int (*stop)(struct watchdog_device *);
	int (*ping)(struct watchdog_device *);
	unsigned int (*status)(struct watchdog_device *);
	int (*set_timeout)(struct watchdog_device *, unsigned int);
	int (*set_pretimeout)(struct watchdog_device *, unsigned int);
	unsigned int (*get_timeleft)(struct watchdog_device *);
	int (*restart)(struct watchdog_device *, unsigned long, void *);
	long (*ioctl)(struct watchdog_device *, unsigned int, unsigned long);
};


/**
 * @brief Watchdog device util structure.
*/
struct watchdog_device {
	int id;
	struct device *parent;
	const struct attribute_group **groups;
	const struct watchdog_info *info;
	const struct watchdog_ops *ops;
	const struct watchdog_governor *gov;
	unsigned int bootstatus;
	unsigned int timeout;
	unsigned int pretimeout;
	unsigned int min_timeout;
	unsigned int max_timeout;
	unsigned int min_hw_heartbeat_ms;
	unsigned int max_hw_heartbeat_ms;
	struct notifier_block reboot_nb;
	struct notifier_block restart_nb;
	struct notifier_block pm_nb;
	void *driver_data;
	struct watchdog_core_data *wd_data;
	unsigned long status;
/* Bit numbers for status flags */
#define WDOG_ACTIVE		0	/* Is the watchdog running/active */
#define WDOG_NO_WAY_OUT		1	/* Is 'nowayout' feature set ? */
#define WDOG_STOP_ON_REBOOT	2	/* Should be stopped on reboot */
#define WDOG_HW_RUNNING		3	/* True if HW watchdog running */
#define WDOG_STOP_ON_UNREGISTER	4	/* Should be stopped on unregister */
#define WDOG_NO_PING_ON_SUSPEND	5	/* Ping worker should be stopped on suspend */
	struct list_head deferred;
};

#define WATCHDOG_NOWAYOUT		IS_BUILTIN(CONFIG_WATCHDOG_NOWAYOUT)
#define WATCHDOG_NOWAYOUT_INIT_STATUS	(WATCHDOG_NOWAYOUT << WDOG_NO_WAY_OUT)


static inline bool watchdog_active(struct watchdog_device *wdd)
{
	return test_bit(WDOG_ACTIVE, &wdd->status);
}

/*
 * Use the following function to check whether or not the hardware watchdog
 * is running
 */
static inline bool watchdog_hw_running(struct watchdog_device *wdd)
{
	return test_bit(WDOG_HW_RUNNING, &wdd->status);
}

/* Use the following function to set the nowayout feature */
static inline void watchdog_set_nowayout(struct watchdog_device *wdd, bool nowayout)
{
	if (nowayout)
		set_bit(WDOG_NO_WAY_OUT, &wdd->status);
}

/* Use the following function to stop the watchdog on reboot */
static inline void watchdog_stop_on_reboot(struct watchdog_device *wdd)
{
	set_bit(WDOG_STOP_ON_REBOOT, &wdd->status);
}

/* Use the following function to stop the watchdog when unregistering it */
static inline void watchdog_stop_on_unregister(struct watchdog_device *wdd)
{
	set_bit(WDOG_STOP_ON_UNREGISTER, &wdd->status);
}

/* Use the following function to stop the wdog ping worker when suspending */
static inline void watchdog_stop_ping_on_suspend(struct watchdog_device *wdd)
{
	set_bit(WDOG_NO_PING_ON_SUSPEND, &wdd->status);
}

/* Use the following function to check if a timeout value is invalid */
static inline bool watchdog_timeout_invalid(struct watchdog_device *wdd, unsigned int t)
{
	/*
	 * The timeout is invalid if
	 * - the requested value is larger than UINT_MAX / 1000
	 *   (since internal calculations are done in milli-seconds),
	 * or
	 * - the requested value is smaller than the configured minimum timeout,
	 * or
	 * - a maximum hardware timeout is not configured, a maximum timeout
	 *   is configured, and the requested value is larger than the
	 *   configured maximum timeout.
	 */
	return t > UINT_MAX / 1000 || t < wdd->min_timeout ||
		(!wdd->max_hw_heartbeat_ms && wdd->max_timeout &&
		 t > wdd->max_timeout);
}

/* Use the following function to check if a pretimeout value is invalid */
static inline bool watchdog_pretimeout_invalid(struct watchdog_device *wdd,
					       unsigned int t)
{
	return t && wdd->timeout && t >= wdd->timeout;
}

/* Use the following functions to manipulate watchdog driver specific data */
static inline void watchdog_set_drvdata(struct watchdog_device *wdd, void *data)
{
	wdd->driver_data = data;
}

static inline void *watchdog_get_drvdata(struct watchdog_device *wdd)
{
	return wdd->driver_data;
}

/* Use the following functions to report watchdog pretimeout event */
#if IS_ENABLED(CONFIG_WATCHDOG_PRETIMEOUT_GOV)
void watchdog_notify_pretimeout(struct watchdog_device *wdd);
#else
static inline void watchdog_notify_pretimeout(struct watchdog_device *wdd)
{
	pr_alert("watchdog%d: pretimeout event\n", wdd->id);
}
#endif /*CONFIG_WATCHDOG_PRETIMEOUT_GOV*/

/* drivers/watchdog/watchdog_core.c */
void watchdog_set_restart_priority(struct watchdog_device *wdd, int priority);
extern int watchdog_init_timeout(struct watchdog_device *wdd,
				  unsigned int timeout_parm, struct device *dev);
extern int watchdog_register_device(struct watchdog_device *);
extern void watchdog_unregister_device(struct watchdog_device *);
int watchdog_dev_suspend(struct watchdog_device *wdd);
int watchdog_dev_resume(struct watchdog_device *wdd);

int watchdog_set_last_hw_keepalive(struct watchdog_device *, unsigned int);

/* devres register variant */
int devm_watchdog_register_device(struct device *dev, struct watchdog_device *);

#endif /* __ALINIX_KERNEL_WATCH_DOG_H */