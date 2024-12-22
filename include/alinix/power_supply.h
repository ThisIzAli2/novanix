/**
 * @author Ali Mirmohammad
 * @file power_supply.h
 * @ref https://github.com/torvalds/linux/blob/master/include/linux/power_supply.h#L344
 * *************************************IMPORTANT ALINIX LICENSE TERM********************************************
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
 * 	- Kernel power implementation.
*/

#ifndef __ALINIX_KERNEL_POWER_SUPPLY_H
#define __ALINIX_KERNEL_POWER_SUPPLY_H

#include <alinix/types.h>
#include <alinix/kconf.h>
#include <alinix/compiler_attributes.h>
#include <alinix/types.h>
#include <alinix/device.h>

#define EILSEQ		88	/* Illegal byte sequence */
#define ENOSYS		89	/* Function not implemented */
#define ELOOP		90	/* Too many symbolic links encountered */
#define ERESTART	91	/* Interrupted system call should be restarted */
#define ESTRPIPE	92	/* Streams pipe error */
#define ENOTEMPTY	93	/* Directory not empty */
#define EUSERS		94	/* Too many users */
#define ENOTSOCK	95	/* Socket operation on non-socket */
#define EDESTADDRREQ	96	/* Destination address required */
#define EMSGSIZE	97	/* Message too long */
#define EPROTOTYPE	98	/* Protocol wrong type for socket */
#define ENOPROTOOPT	99	/* Protocol not available */
#define EPROTONOSUPPORT 120	/* Protocol not supported */
#define ESOCKTNOSUPPORT 121	/* Socket type not supported */
#define EOPNOTSUPP	122	/* Operation not supported on transport endpoint */
#define EPFNOSUPPORT	123	/* Protocol family not supported */
#define EAFNOSUPPORT	124	/* Address family not supported by protocol */
#define EADDRINUSE	125	/* Address already in use */
#define EADDRNOTAVAIL	126	/* Cannot assign requested address */
#define ENETDOWN	127	/* Network is down */
#define ENETUNREACH	128	/* Network is unreachable */
#define ENETRESET	129	/* Network dropped connection because of reset */
#define ECONNABORTED	130	/* Software caused connection abort */
#define ECONNRESET	131	

enum power_supply_charge_behaviour {
	POWER_SUPPLY_CHARGE_BEHAVIOUR_AUTO = 0,
	POWER_SUPPLY_CHARGE_BEHAVIOUR_INHIBIT_CHARGE,
	POWER_SUPPLY_CHARGE_BEHAVIOUR_FORCE_DISCHARGE,
};

enum power_supply_property {
	/* Properties of type `int' */
	POWER_SUPPLY_PROP_STATUS = 0,
	POWER_SUPPLY_PROP_CHARGE_TYPE,
	POWER_SUPPLY_PROP_HEALTH,
	POWER_SUPPLY_PROP_PRESENT,
	POWER_SUPPLY_PROP_ONLINE,
	POWER_SUPPLY_PROP_AUTHENTIC,
	POWER_SUPPLY_PROP_TECHNOLOGY,
	POWER_SUPPLY_PROP_CYCLE_COUNT,
	POWER_SUPPLY_PROP_VOLTAGE_MAX,
	POWER_SUPPLY_PROP_VOLTAGE_MIN,
	POWER_SUPPLY_PROP_VOLTAGE_MAX_DESIGN,
	POWER_SUPPLY_PROP_VOLTAGE_MIN_DESIGN,
	POWER_SUPPLY_PROP_VOLTAGE_NOW,
	POWER_SUPPLY_PROP_VOLTAGE_AVG,
	POWER_SUPPLY_PROP_VOLTAGE_OCV,
	POWER_SUPPLY_PROP_VOLTAGE_BOOT,
	POWER_SUPPLY_PROP_CURRENT_MAX,
	POWER_SUPPLY_PROP_CURRENT_NOW,
	POWER_SUPPLY_PROP_CURRENT_AVG,
	POWER_SUPPLY_PROP_CURRENT_BOOT,
	POWER_SUPPLY_PROP_POWER_NOW,
	POWER_SUPPLY_PROP_POWER_AVG,
	POWER_SUPPLY_PROP_CHARGE_FULL_DESIGN,
	POWER_SUPPLY_PROP_CHARGE_EMPTY_DESIGN,
	POWER_SUPPLY_PROP_CHARGE_FULL,
	POWER_SUPPLY_PROP_CHARGE_EMPTY,
	POWER_SUPPLY_PROP_CHARGE_NOW,
	POWER_SUPPLY_PROP_CHARGE_AVG,
	POWER_SUPPLY_PROP_CHARGE_COUNTER,
	POWER_SUPPLY_PROP_CONSTANT_CHARGE_CURRENT,
	POWER_SUPPLY_PROP_CONSTANT_CHARGE_CURRENT_MAX,
	POWER_SUPPLY_PROP_CONSTANT_CHARGE_VOLTAGE,
	POWER_SUPPLY_PROP_CONSTANT_CHARGE_VOLTAGE_MAX,
	POWER_SUPPLY_PROP_CHARGE_CONTROL_LIMIT,
	POWER_SUPPLY_PROP_CHARGE_CONTROL_LIMIT_MAX,
	POWER_SUPPLY_PROP_CHARGE_CONTROL_START_THRESHOLD, /* in percents! */
	POWER_SUPPLY_PROP_CHARGE_CONTROL_END_THRESHOLD, /* in percents! */
	POWER_SUPPLY_PROP_CHARGE_BEHAVIOUR,
	POWER_SUPPLY_PROP_INPUT_CURRENT_LIMIT,
	POWER_SUPPLY_PROP_INPUT_VOLTAGE_LIMIT,
	POWER_SUPPLY_PROP_INPUT_POWER_LIMIT,
	POWER_SUPPLY_PROP_ENERGY_FULL_DESIGN,
	POWER_SUPPLY_PROP_ENERGY_EMPTY_DESIGN,
	POWER_SUPPLY_PROP_ENERGY_FULL,
	POWER_SUPPLY_PROP_ENERGY_EMPTY,
	POWER_SUPPLY_PROP_ENERGY_NOW,
	POWER_SUPPLY_PROP_ENERGY_AVG,
	POWER_SUPPLY_PROP_CAPACITY, /* in percents! */
	POWER_SUPPLY_PROP_CAPACITY_ALERT_MIN, /* in percents! */
	POWER_SUPPLY_PROP_CAPACITY_ALERT_MAX, /* in percents! */
	POWER_SUPPLY_PROP_CAPACITY_ERROR_MARGIN, /* in percents! */
	POWER_SUPPLY_PROP_CAPACITY_LEVEL,
	POWER_SUPPLY_PROP_TEMP,
	POWER_SUPPLY_PROP_TEMP_MAX,
	POWER_SUPPLY_PROP_TEMP_MIN,
	POWER_SUPPLY_PROP_TEMP_ALERT_MIN,
	POWER_SUPPLY_PROP_TEMP_ALERT_MAX,
	POWER_SUPPLY_PROP_TEMP_AMBIENT,
	POWER_SUPPLY_PROP_TEMP_AMBIENT_ALERT_MIN,
	POWER_SUPPLY_PROP_TEMP_AMBIENT_ALERT_MAX,
	POWER_SUPPLY_PROP_TIME_TO_EMPTY_NOW,
	POWER_SUPPLY_PROP_TIME_TO_EMPTY_AVG,
	POWER_SUPPLY_PROP_TIME_TO_FULL_NOW,
	POWER_SUPPLY_PROP_TIME_TO_FULL_AVG,
	POWER_SUPPLY_PROP_TYPE, /* use power_supply.type instead */
	POWER_SUPPLY_PROP_USB_TYPE,
	POWER_SUPPLY_PROP_SCOPE,
	POWER_SUPPLY_PROP_PRECHARGE_CURRENT,
	POWER_SUPPLY_PROP_CHARGE_TERM_CURRENT,
	POWER_SUPPLY_PROP_CALIBRATE,
	POWER_SUPPLY_PROP_MANUFACTURE_YEAR,
	POWER_SUPPLY_PROP_MANUFACTURE_MONTH,
	POWER_SUPPLY_PROP_MANUFACTURE_DAY,
	/* Properties of type `const char *' */
	POWER_SUPPLY_PROP_MODEL_NAME,
	POWER_SUPPLY_PROP_MANUFACTURER,
	POWER_SUPPLY_PROP_SERIAL_NUMBER,
};

struct power_supply_battery_ocv_table{
    int ocv; // capacity
    int capacity; // microvolt 
};


struct power_supply_resistance_temp_table {
	int temp;	/* celsius */
	int resistance;	/* internal resistance percent */
};

struct power_supply_vbat_ri_table {
	int vbat_uv;	/* Battery voltage in microvolt */
	int ri_uohm;	/* Internal resistance in microohm */
};

struct power_supply_maintenance_charge_table {
	int charge_current_max_ua;
	int charge_voltage_max_uv;
	int charge_safety_timer_minutes;
};


#define POWER_SUPPLY_OCV_TEMP_MAX 20

struct power_supply_battery_info{
    POSITIVE technology;
	int energy_full_design_uwh;
	int charge_full_design_uah;
	int voltage_min_design_uv;
	int voltage_max_design_uv;
	int tricklecharge_current_ua;
	int precharge_current_ua;
	int precharge_voltage_max_uv;
	int charge_term_current_ua;
	int charge_restart_voltage_uv;
	int overvoltage_limit_uv;
	int constant_charge_current_max_ua;
	int constant_charge_voltage_max_uv;
    struct power_supply_maintenance_charge_table *maintenance_charge;
    int maintenance_charge_size;
	int alert_low_temp_charge_current_ua;
	int alert_low_temp_charge_voltage_uv;
	int alert_high_temp_charge_current_ua;
	int alert_high_temp_charge_voltage_uv;
	int factory_internal_resistance_uohm;
	int factory_internal_resistance_charging_uohm;
	int ocv_temp[POWER_SUPPLY_OCV_TEMP_MAX];
	int temp_ambient_alert_min;
	int temp_ambient_alert_max;
	int temp_alert_min;
	int temp_alert_max;
	int temp_min;
	int temp_max;
    struct power_supply_battery_ocv_table *ocv_table[POWER_SUPPLY_OCV_TEMP_MAX];
	int ocv_table_size[POWER_SUPPLY_OCV_TEMP_MAX];
	struct power_supply_resistance_temp_table *resist_table;
	int resist_table_size;
	struct power_supply_vbat_ri_table *vbat2ri_discharging;
	int vbat2ri_discharging_size;
	struct power_supply_vbat_ri_table *vbat2ri_charging;
	int vbat2ri_charging_size;
	int bti_resistance_ohm;
	int bti_resistance_tolerance;
};


extern int power_supply_reg_notifier(struct notifier_block *nb);
extern void power_supply_unreg_notifier(struct notifier_block *nb);
#if IS_ENABLED(CONFIG_POWER_SUPPLY)
extern struct power_supply *power_supply_get_by_name(const char *name);
extern void power_supply_put(struct power_supply *psy);
#else
static inline void power_supply_put(struct power_supply *psy) {}
static inline struct power_supply *power_supply_get_by_name(const char *name)
{ return NULL; }
#endif /*CONFIG_POWER_SUPPLY*/
#ifdef CONFIG_OF
extern struct power_supply *power_supply_get_by_phandle(struct device_node *np,
							const char *property);
extern struct power_supply *devm_power_supply_get_by_phandle(
				    struct device *dev, const char *property);
#else /* !CONFIG_OF */
static inline struct power_supply *
power_supply_get_by_phandle(struct device_node *np, const char *property)
{ return NULL; }
static inline struct power_supply *
devm_power_supply_get_by_phandle(struct device *dev, const char *property)
{ return NULL; }
#endif /* CONFIG_OF */

extern const enum power_supply_property power_supply_battery_info_properties[];
extern const size_t power_supply_battery_info_properties_size;
extern int power_supply_get_battery_info(struct power_supply *psy,
					 struct power_supply_battery_info **info_out);
extern void power_supply_put_battery_info(struct power_supply *psy,
					  struct power_supply_battery_info *info);
extern bool power_supply_battery_info_has_prop(struct power_supply_battery_info *info,
					       enum power_supply_property psp);
extern int power_supply_battery_info_get_prop(struct power_supply_battery_info *info,
					      enum power_supply_property psp,
					      union power_supply_propval *val);
extern int power_supply_ocv2cap_simple(struct power_supply_battery_ocv_table *table,
				       int table_len, int ocv);
extern struct power_supply_battery_ocv_table *
power_supply_find_ocv2cap_table(struct power_supply_battery_info *info,
				int temp, int *table_len);
extern int power_supply_batinfo_ocv2cap(struct power_supply_battery_info *info,
					int ocv, int temp);
extern int
power_supply_temp2resist_simple(struct power_supply_resistance_temp_table *table,
				int table_len, int temp);
extern int power_supply_vbat2ri(struct power_supply_battery_info *info,
				int vbat_uv, bool charging);
extern struct power_supply_maintenance_charge_table *
power_supply_get_maintenance_charging_setting(struct power_supply_battery_info *info, int index);
extern bool power_supply_battery_bti_in_range(struct power_supply_battery_info *info,
					      int resistance);
extern void power_supply_changed(struct power_supply *psy);
extern int power_supply_am_i_supplied(struct power_supply *psy);
int power_supply_get_property_from_supplier(struct power_supply *psy,
					    enum power_supply_property psp,
					    union power_supply_propval *val);
extern int power_supply_set_battery_charged(struct power_supply *psy);

static inline bool
power_supply_supports_maintenance_charging(struct power_supply_battery_info *info)
{
	struct power_supply_maintenance_charge_table *mt;

	mt = power_supply_get_maintenance_charging_setting(info, 0);

	return (mt != NULL);
}

static inline bool
power_supply_supports_vbat2ri(struct power_supply_battery_info *info)
{
	return ((info->vbat2ri_discharging != NULL) &&
		info->vbat2ri_discharging_size > 0);
}

static inline bool
power_supply_supports_temp2ri(struct power_supply_battery_info *info)
{
	return ((info->resist_table != NULL) &&
		info->resist_table_size > 0);
}

#ifdef CONFIG_POWER_SUPPLY
extern int power_supply_is_system_supplied(void);
#else
static inline int power_supply_is_system_supplied(void) { return -ENOSYS; }
#endif /*CONFIG_POWER_SUPPLY*/

extern int power_supply_get_property(struct power_supply *psy,
			    enum power_supply_property psp,
			    union power_supply_propval *val);
#if IS_ENABLED(CONFIG_POWER_SUPPLY)
extern int power_supply_set_property(struct power_supply *psy,
			    enum power_supply_property psp,
			    const union power_supply_propval *val);
#else
static inline int power_supply_set_property(struct power_supply *psy,
			    enum power_supply_property psp,
			    const union power_supply_propval *val)
{ return 0; }
#endif /*CONFIG_POWER_SUPPLY*/
extern int power_supply_property_is_writeable(struct power_supply *psy,
					enum power_supply_property psp);
extern void power_supply_external_power_changed(struct power_supply *psy);

extern struct power_supply *__must_check
power_supply_register(struct device *parent,
				 const struct power_supply_desc *desc,
				 const struct power_supply_config *cfg);
extern struct power_supply *__must_check
power_supply_register_no_ws(struct device *parent,
				 const struct power_supply_desc *desc,
				 const struct power_supply_config *cfg);
extern struct power_supply *__must_check
devm_power_supply_register(struct device *parent,
				 const struct power_supply_desc *desc,
				 const struct power_supply_config *cfg);
extern struct power_supply *__must_check
devm_power_supply_register_no_ws(struct device *parent,
				 const struct power_supply_desc *desc,
				 const struct power_supply_config *cfg);
extern void power_supply_unregister(struct power_supply *psy);
extern int power_supply_powers(struct power_supply *psy, struct device *dev);

#define to_power_supply(device) container_of(device, struct power_supply, dev)

extern void *power_supply_get_drvdata(struct power_supply *psy);
extern int power_supply_for_each_device(void *data, int (*fn)(struct device *dev, void *data));

/**
 * power_supply_is_amp_property - Check if a power supply property is an ampere property
 * @psp: The power supply property to check, of type enum power_supply_property
 *
 * This function determines if the given power supply property represents a measurement
 * related to current (in amperes). It checks if the provided property matches any of
 * the predefined properties that are associated with current measurements.
 *
 * Return: true if the property is related to current, false otherwise.
 */
static inline bool power_supply_is_amp_property(enum power_supply_property psp)
{
	switch (psp) {
	case POWER_SUPPLY_PROP_CHARGE_FULL_DESIGN:
	case POWER_SUPPLY_PROP_CHARGE_EMPTY_DESIGN:
	case POWER_SUPPLY_PROP_CHARGE_FULL:
	case POWER_SUPPLY_PROP_CHARGE_EMPTY:
	case POWER_SUPPLY_PROP_CHARGE_NOW:
	case POWER_SUPPLY_PROP_CHARGE_AVG:
	case POWER_SUPPLY_PROP_CHARGE_COUNTER:
	case POWER_SUPPLY_PROP_PRECHARGE_CURRENT:
	case POWER_SUPPLY_PROP_CHARGE_TERM_CURRENT:
	case POWER_SUPPLY_PROP_CONSTANT_CHARGE_CURRENT:
	case POWER_SUPPLY_PROP_CONSTANT_CHARGE_CURRENT_MAX:
	case POWER_SUPPLY_PROP_CURRENT_MAX:
	case POWER_SUPPLY_PROP_CURRENT_NOW:
	case POWER_SUPPLY_PROP_CURRENT_AVG:
	case POWER_SUPPLY_PROP_CURRENT_BOOT:
		return true;
	default:
		break;
	}

	return false;
}

/**
 * power_supply_is_watt_property - Check if a power supply property is a wattage property
 * @psp: The power supply property to check, of type enum power_supply_property
 *
 * This function determines if the given power supply property represents a measurement
 * related to power (in watts) or voltage. It checks if the provided property matches any of
 * the predefined properties that are associated with energy measurements.
 *
 * Return: true if the property is related to power or voltage, false otherwise.
 */
static inline bool power_supply_is_watt_property(enum power_supply_property psp)
{
	switch (psp) {
	case POWER_SUPPLY_PROP_ENERGY_FULL_DESIGN:
	case POWER_SUPPLY_PROP_ENERGY_EMPTY_DESIGN:
	case POWER_SUPPLY_PROP_ENERGY_FULL:
	case POWER_SUPPLY_PROP_ENERGY_EMPTY:
	case POWER_SUPPLY_PROP_ENERGY_NOW:
	case POWER_SUPPLY_PROP_ENERGY_AVG:
	case POWER_SUPPLY_PROP_VOLTAGE_MAX:
	case POWER_SUPPLY_PROP_VOLTAGE_MIN:
	case POWER_SUPPLY_PROP_VOLTAGE_MAX_DESIGN:
	case POWER_SUPPLY_PROP_VOLTAGE_MIN_DESIGN:
	case POWER_SUPPLY_PROP_VOLTAGE_NOW:
	case POWER_SUPPLY_PROP_VOLTAGE_AVG:
	case POWER_SUPPLY_PROP_VOLTAGE_OCV:
	case POWER_SUPPLY_PROP_VOLTAGE_BOOT:
	case POWER_SUPPLY_PROP_CONSTANT_CHARGE_VOLTAGE:
	case POWER_SUPPLY_PROP_CONSTANT_CHARGE_VOLTAGE_MAX:
	case POWER_SUPPLY_PROP_POWER_NOW:
		return true;
	default:
		break;
	}

	return false;
}

#ifdef CONFIG_POWER_SUPPLY_HWMON
int power_supply_add_hwmon_sysfs(struct power_supply *psy);
void power_supply_remove_hwmon_sysfs(struct power_supply *psy);
#else

/**
 * power_supply_add_hwmon_sysfs - Add hwmon sysfs entries for a power supply
 * @psy: Pointer to the power_supply structure representing the power supply
 *
 * This function is intended to add hardware monitoring (hwmon) sysfs entries
 * for a given power supply. However, the current implementation does not
 * perform any operation and always returns 0, indicating success.
 *
 * Return: 0, indicating success.
 */
static inline int power_supply_add_hwmon_sysfs(struct power_supply *psy)
{
	return 0;
}

static inline
void power_supply_remove_hwmon_sysfs(struct power_supply *psy) {}
#endif /*CONFIG_POWER_SUPPLY_HWMON*/

#ifdef CONFIG_SYSFS
ssize_t power_supply_charge_behaviour_show(struct device *dev,
					   unsigned int available_behaviours,
					   enum power_supply_charge_behaviour behaviour,
					   char *buf);

int power_supply_charge_behaviour_parse(unsigned int available_behaviours, const char *buf);
#else

/**
 * power_supply_charge_behaviour_show - Show the charge behavior of a power supply
 * @dev: The device representing the power supply
 * @available_behaviours: Bitmask of available charge behaviors
 * @behaviour: The current charge behavior of the power supply
 * @buf: Buffer to store the output string representing the charge behavior
 *
 * This function is intended to display the current charge behavior of a power supply
 * by writing it to the provided buffer. However, the current implementation does not
 * support this operation and always returns -EOPNOTSUPP, indicating that the operation
 * is not supported.
 *
 * Return: -EOPNOTSUPP, indicating the operation is not supported.
 */
static inline
ssize_t power_supply_charge_behaviour_show(struct device *dev,
					   unsigned int available_behaviours,
					   enum power_supply_charge_behaviour behaviour,
					   char *buf)
{
	return -EOPNOTSUPP;
}

/**
 * power_supply_charge_behaviour_parse - Parse charge behavior for a power supply
 * @available_behaviours: Bitmask of available charge behaviors
 * @buf: Input buffer containing the behavior to be parsed
 *
 * This function is intended to parse the charge behavior for a power supply.
 * However, the current implementation does not support this operation and
 * always returns -EOPNOTSUPP, indicating that the operation is not supported.
 *
 * Return: -EOPNOTSUPP, indicating the operation is not supported.
 */
static inline int power_supply_charge_behaviour_parse(unsigned int available_behaviours,
						      const char *buf)
{
	return -EOPNOTSUPP;
}
#endif /*CONFIG_SYSFS*/

#endif /*__ALINIX_KERNEL_POWER_SUPPLY_H*/