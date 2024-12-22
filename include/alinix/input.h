/**
 * @author Ali Mirmohammad
 * @file input.h
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
 * @abstract:
 * 	- Kernel implementation input header file implemented.
*/
#ifndef __ALINIX_KERNEL_INPUT_H
#define __ALINIX_KERNEL_INPUT_H

#include <alinix/types.h>
#include <alinix/device.h>
#include <alinix/mutex_types.h>
#include <alinix/spinlock_types.h>
#include <alinix/timer_types.h>
#include <alinix/event-code.h>


struct input_handler;

struct input_mt {
	int trkid;
	int num_slots;
	int slot;
	unsigned int flags;
	unsigned int frame;
	int *red;
};

struct input_keymap_entry {
#define INPUT_KEYMAP_BY_INDEX	(1 << 0)
	u8  flags;
	u8  len;
	u16 index;
	u32 keycode;
	u8  scancode[32];
};

struct input_value {
	u16 type;
	u16 code;
	sint32_t value;
};

enum input_clock_type {
	INPUT_CLK_REAL = 0,
	INPUT_CLK_MONO,
	INPUT_CLK_BOOT,
	INPUT_CLK_MAX
};

struct input_id {
	u16 bustype;
	u16 vendor;
	u16 product;
	u16 version;
};


struct input_dev {
	const char *name;
	const char *phys;
	const char *uniq;
	struct input_id id;

	unsigned long propbit[INPUT_PROP_CNT];

	unsigned long evbit[EV_CNT];
	unsigned long keybit[KEY_CNT];
	unsigned long relbit[REL_CNT];
	unsigned long absbit[ABS_CNT];
	unsigned long mscbit[MSC_CNT];
	unsigned long ledbit[LED_CNT];
	unsigned long sndbit[SND_CNT];
	unsigned long ffbit[SND_CNT];
	unsigned long swbit[SW_CNT];

	unsigned int hint_events_per_packet;

	unsigned int keycodemax;
	unsigned int keycodesize;
	void *keycode;

	int (*setkeycode)(struct input_dev *dev,
			  const struct input_keymap_entry *ke,
			  unsigned int *old_keycode);
	int (*getkeycode)(struct input_dev *dev,
			  struct input_keymap_entry *ke);

	struct ff_device *ff;

	struct input_dev_poller *poller;

	unsigned int repeat_key;
	struct timer_list timer;

	int rep[REP_CNT];

	struct input_mt *mt;

	struct input_absinfo *absinfo;

	unsigned long key[(KEY_CNT)];
	unsigned long led[(LED_CNT)];
	unsigned long snd[(SND_CNT)];
	unsigned long sw[(SW_CNT)];

	int (*open)(struct input_dev *dev);
	void (*close)(struct input_dev *dev);
	int (*flush)(struct input_dev *dev);
	int (*event)(struct input_dev *dev, unsigned int type, unsigned int code, int value);

	struct input_handle  *grab;

	spinlock_t event_lock;
	struct mutex mutex;

	unsigned int users;
	bool going_away;

	struct device dev;

	struct list_head	h_list;
	struct list_head	node;

	unsigned int num_vals;
	unsigned int max_vals;
	struct input_value *vals;

	bool devres_managed;

	ktime_t timestamp[INPUT_CLK_MAX];

	bool inhibited;
};

struct input_handler {

	// void *private;

	void (*event)(struct input_handle *handle, unsigned int type, unsigned int code, int value);
	void (*events)(struct input_handle *handle,
		       const struct input_value *vals, unsigned int count);
	bool (*filter)(struct input_handle *handle, unsigned int type, unsigned int code, int value);
	bool (*match)(struct input_handler *handler, struct input_dev *dev);
	int (*connect)(struct input_handler *handler, struct input_dev *dev, const struct input_device_id *id);
	void (*disconnect)(struct input_handle *handle);
	void (*start)(struct input_handle *handle);

	bool legacy_minors;
	int minor;
	const char *name;

	const struct input_device_id *id_table;

	struct list_head	h_list;
	struct list_head	node;
};


void input_event(struct input_dev *dev, unsigned int type, unsigned int code, int value);
void input_inject_event(struct input_handle *handle, unsigned int type, unsigned int code, int value);


/**
 * input_report_key - Report a key press or release event
 * @dev: input device to report the event for
 * @code: key code to report
 * @value: value to report (0 for key release, non-zero for key press)
 *
 * This function generates and reports a key press or release event
 * for the specified input device. It is typically used in input drivers
 * to notify the input subsystem of key state changes.
 *
 * The function calls `input_event` with the event type set to `EV_KEY`,
 * the specified key code, and a boolean value indicating whether the key
 * is pressed (`!!value`).
 *
 * Example usage:
 *     input_report_key(dev, KEY_A, 1); // Report key press for 'A'
 *     input_report_key(dev, KEY_A, 0); // Report key release for 'A'
 */
static inline void input_report_key(struct input_dev *dev, unsigned int code, int value)
{
	input_event(dev, EV_KEY, code, !!value);
}

/**
 * input_report_rel - Report a relative movement event
 * @dev: input device to report the event for
 * @code: relative axis code to report
 * @value: relative movement value
 *
 * This function generates and reports a relative movement event
 * for the specified input device. It is typically used in input drivers
 * to notify the input subsystem of changes in relative position, such as
 * mouse movements or scroll wheel activity.
 *
 * The function calls `input_event` with the event type set to `EV_REL`,
 * the specified axis code, and the movement value.
 *
 * Example usage:
 *     input_report_rel(dev, REL_X, 10); // Report relative movement on the X axis
 *     input_report_rel(dev, REL_Y, -5); // Report relative movement on the Y axis
 */
static inline void input_report_rel(struct input_dev *dev, unsigned int code, int value)
{
	input_event(dev, EV_REL, code, value);
}

/**
 * input_report_abs - Report an absolute axis event
 * @dev: input device to report the event for
 * @code: absolute axis code to report
 * @value: absolute position value
 *
 * This function generates and reports an absolute axis event
 * for the specified input device. It is typically used in input drivers
 * to notify the input subsystem of changes in absolute position, such as
 * touch screen coordinates or joystick positions.
 *
 * The function calls `input_event` with the event type set to `EV_ABS`,
 * the specified axis code, and the position value.
 *
 * Example usage:
 *     input_report_abs(dev, ABS_X, 200); // Report absolute position on the X axis
 *     input_report_abs(dev, ABS_Y, 150); // Report absolute position on the Y axis
 */
static inline void input_report_abs(struct input_dev *dev, unsigned int code, int value)
{
	input_event(dev, EV_ABS, code, value);
}

/**
 * input_report_ff_status - Report force feedback status event
 * @dev: input device to report the event for
 * @code: force feedback effect code to report
 * @value: status value of the force feedback effect
 *
 * This function generates and reports a force feedback (FF) status event
 * for the specified input device. It is typically used in input drivers
 * to notify the input subsystem of changes in the status of force feedback
 * effects, such as starting, stopping, or updating an effect.
 *
 * The function calls `input_event` with the event type set to `EV_FF_STATUS`,
 * the specified effect code, and the status value.
 *
 * Example usage:
 *     input_report_ff_status(dev, FF_RUMBLE, 1); // Report starting of rumble effect
 *     input_report_ff_status(dev, FF_RUMBLE, 0); // Report stopping of rumble effect
 */
static inline void input_report_ff_status(struct input_dev *dev, unsigned int code, int value)
{
	input_event(dev, EV_FF_STATUS, code, value);
}


/**
 * input_report_switch - Report a switch state change event
 * @dev: input device to report the event for
 * @code: switch code to report
 * @value: state value of the switch (0 for off, non-zero for on)
 *
 * This function generates and reports a switch state change event
 * for the specified input device. It is typically used in input drivers
 * to notify the input subsystem of changes in the state of switches,
 * such as lid open/close or tablet mode switches.
 *
 * The function calls `input_event` with the event type set to `EV_SW`,
 * the specified switch code, and a boolean value indicating whether the
 * switch is on (`!!value`).
 *
 * Example usage:
 *     input_report_switch(dev, SW_LID, 1); // Report lid switch as closed
 *     input_report_switch(dev, SW_LID, 0); // Report lid switch as open
 */
static inline void input_report_switch(struct input_dev *dev, unsigned int code, int value)
{
	input_event(dev, EV_SW, code, !!value);
}

/**
 * input_sync - Synchronize input device events
 * @dev: input device to synchronize
 *
 * This function generates and reports a synchronization event for the
 * specified input device. It is typically used in input drivers to mark
 * the end of a set of input events, ensuring that the input subsystem
 * processes the events as a coherent group.
 *
 * The function calls `input_event` with the event type set to `EV_SYN`
 * and the event code set to `SYN_REPORT`. The value parameter is set to 0,
 * indicating the end of the event reporting.
 *
 * Example usage:
 *     input_report_key(dev, KEY_A, 1); // Report key press for 'A'
 *     input_sync(dev);                 // Synchronize the event
 */
static inline void input_sync(struct input_dev *dev)
{
	input_event(dev, EV_SYN, SYN_REPORT, 0);
}

/**
 * input_mt_sync - Synchronize multi-touch events
 * @dev: input device to synchronize
 *
 * This function generates and reports a multi-touch synchronization event for the
 * specified input device. It is typically used in input drivers to mark the end of
 * a set of multi-touch input events, ensuring that the input subsystem processes
 * the events as a coherent group.
 *
 * The function calls `input_event` with the event type set to `EV_SYN`,
 * the event code set to `SYN_MT_REPORT`, and the value parameter set to 0,
 * indicating the end of the multi-touch event reporting.
 *
 * Example usage:
 *     input_mt_slot(dev, 0);          // Select the first touch slot
 *     input_report_abs(dev, ABS_MT_POSITION_X, 100); // Report X coordinate
 *     input_report_abs(dev, ABS_MT_POSITION_Y, 150); // Report Y coordinate
 *     input_mt_sync(dev);             // Synchronize the multi-touch event
 */
static inline void input_mt_sync(struct input_dev *dev)
{
	input_event(dev, EV_SYN, SYN_MT_REPORT, 0);
}



#endif /*__ALINIX_KERNEL_INPUT_H*/