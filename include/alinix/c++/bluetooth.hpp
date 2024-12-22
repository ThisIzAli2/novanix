/**
 * @file bluetooth.h
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
 *  - Provides bluetooth util for C++ section.
*/
#ifndef __ALINIX_KERNEL_C_PLUS_PLUS_BLUETOOTH_HPP
#define __ALINIX_KERNEL_C_PLUS_PLUS_BLUETOOTH_HPP


#include <alinix/types.h>
#include <alinix/list.h>
#include <alinix/gpio/desc.h>
#include <alinix/clk.h>
#include <alinix/skbuff.h>


#define BCM_NULL_PKT 0x00
#define BCM_NULL_SIZE 0

#define BCM_LM_DIAG_PKT 0x07
#define BCM_LM_DIAG_SIZE 63

#define BCM_TYPE49_PKT 0x31
#define BCM_TYPE49_SIZE 0

#define BCM_TYPE52_PKT 0x34
#define BCM_TYPE52_SIZE 0

#define BCM_AUTOSUSPEND_DELAY	5000 /* default autosleep delay */

#define BCM_NUM_SUPPLIES 2


struct bcm_data {
	struct sk_buff		*rx_skb;
	struct sk_buff_head	txq;

	struct bcm_device	*dev;
};


class Bluetooth{
    public:
        struct list_head    list;
        uint8_t status;
        uint16_t devices;
        uint16_t services;
        uint16_t characteristics;
        uint8_t* uuid;
        struct device *dev;
        const char* name;
        struct gpio_desc *device_wake_up;
        struct gpio_desc	*shutdown;
        int			(*set_device_wakeup)(struct bcm_device *, bool);
        int			(*set_shutdown)(struct bcm_device *, bool);
        bool res_enabled;
        struct clk		*txco_clk;
        struct clk		*lpo_clk;
        bool			res_enabled;

        u32			init_speed;
        u32			oper_speed;
        int			irq;
        bool			irq_active_low;


        Bluetooth();
        ~Bluetooth();
        void Setup();
        bool GetDeviceList();
        bool GetServiceList();
        bool GetCharacteristics();

};



static int irq_polarity = -1;

#ifdef __cplusplus
extern "C" {
#endif /*__cplusplus*/
struct list_head    list;
uint8_t status;
uint16_t devices;
uint16_t services;
uint16_t characteristics;
uint8_t* uuid;
struct device *dev;
const char* name;
struct gpio_desc *device_wake_up;
struct gpio_desc	*shutdown;
int			(*set_device_wakeup)(struct bcm_device *, bool);
int			(*set_shutdown)(struct bcm_device *, bool);
bool res_enabled;
struct clk		*txco_clk;
struct clk		*lpo_clk;
bool			res_enabled;

u32			init_speed;
u32			oper_speed;
int			irq;
bool			irq_active_low;

void Setup();
bool GetDeviceList();
bool GetServiceList();
bool GetCharacteristics();

#ifdef __cplusplus
}
#endif /*__cplusplus*/




#endif // __ALINIX_KERNEL_C_PLUS_PLUS_BLUETOOTH_HPP