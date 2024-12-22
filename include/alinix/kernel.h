/**
 * @author Ali Mirmohammad
 * @file kernel.h
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
 *  - Main header file for the kernel.
 *  - Needed files for the kernel are all included here.
*/

#ifndef _ALINIX_KERNEL_KERNEL_H__
#define _ALINIX_KERNEL_KERNEL_H__

#include <alinix/enums.h>
#include <alinix/syscall.h>
#include <alinix/types.h>
#include <alinix/init.h>
#include <alinix/power_supply.h>
#include <alinix/device.h>
#include <alinix/list.h>

#define ENOMEM 12
#define unlikely

#define __init


/**
 * @brief VGA entry type for the kernel.
*/
typedef struct{
	char character;
	uint8_t color;
} __attribute__((__packed__)) vga_entry_t;

struct kparam_string {
	unsigned int maxlen;
	char *string;
};


struct kernel_param {
	const char *name;
	struct module *mod;
	const struct kernel_param_ops *ops;
	const uint16_t perm;
	sint8_t level;
	uint8_t flags;
	union {
		void *arg;
		const struct kparam_string *str;
		const struct kparam_array *arr;
	};
};

struct kernel_param_ops {
	/* How the ops should behave */
	unsigned int flags;
	/* Returns 0, or -errno.  arg is in kp->arg. */
	int (*set)(const char *val, const struct kernel_param *kp);
	/* Returns length written or -errno.  Buffer is 4k (ie. be short!) */
	int (*get)(char *buffer, const struct kernel_param *kp);
	/* Optional function to free kp->arg when module unloaded. */
	void (*free)(void *arg);
};


vga_entry_t terminal_make_vga_entry(char c);
void terminal_writeline(char* string);
void terminal_scroll();
void terminal_reset_scroll();
void terminal_set_cursor_position(uint8_t x, uint8_t y);
void terminal_write_next_entry(vga_entry_t entry);
void terminal_write_next_char(char c);
void terminal_write_char_at(uint16_t x, uint16_t y, vga_entry_t entry);
void print(char* str,...);
long srm_printk(const char *fmt, ...);
int sprintf(char * buf, const char *fmt, ...);
int vsprintf(char *buf, const char *fmt, va_list args);
long srm_puts(const char* str,long len);
/////////////////////////////////
#define pr_warn print
#define printk print
#define pr_notice print
#define WARN  pr_warn
#define pr_err  printk
#define perror print
#define pr_alert print


/**
 * @brief Structure for the basic address of kernel.
*/
typedef struct GenericAddressStructure
{
  uint8_t AddressSpace;
  uint8_t BitWidth;
  uint8_t BitOffset;
  uint8_t AccessSize;
  uint64_t Address;
}GenericAddressStructure;


struct FADT
{
    uint32_t FirmwareCtrl;
    uint32_t Dsdt;
 
    // field used in ACPI 1.0; no longer in use, for compatibility only
    uint8_t  Reserved;
 
    uint8_t  PreferredPowerManagementProfile;
    uint16_t SCI_Interrupt;
    uint32_t SMI_CommandPort;
    uint8_t  AcpiEnable;
    uint8_t  AcpiDisable;
    uint8_t  S4BIOS_REQ;
    uint8_t  PSTATE_Control;
    uint32_t PM1aEventBlock;
    uint32_t PM1bEventBlock;
    uint32_t PM1aControlBlock;
    uint32_t PM1bControlBlock;
    uint32_t PM2ControlBlock;
    uint32_t PMTimerBlock;
    uint32_t GPE0Block;
    uint32_t GPE1Block;
    uint8_t  PM1EventLength;
    uint8_t  PM1ControlLength;
    uint8_t  PM2ControlLength;
    uint8_t  PMTimerLength;
    uint8_t  GPE0Length;
    uint8_t  GPE1Length;
    uint8_t  GPE1Base;
    uint8_t  CStateControl;
    uint16_t WorstC2Latency;
    uint16_t WorstC3Latency;
    uint16_t FlushSize;
    uint16_t FlushStride;
    uint8_t  DutyOffset;
    uint8_t  DutyWidth;
    uint8_t  DayAlarm;
    uint8_t  MonthAlarm;
    uint8_t  Century;
 
    // reserved in ACPI 1.0; used since ACPI 2.0+
    uint16_t BootArchitectureFlags;
 
    uint8_t  Reserved2;
    uint32_t Flags;
 
    // 12 byte structure; see below for details
    GenericAddressStructure ResetReg;
 
    uint8_t  ResetValue;
    uint8_t  Reserved3[3];
 
    // 64bit pointers - Available on ACPI 2.0+
    uint64_t                X_FirmwareControl;
    uint64_t                X_Dsdt;
 
    GenericAddressStructure X_PM1aEventBlock;
    GenericAddressStructure X_PM1bEventBlock;
    GenericAddressStructure X_PM1aControlBlock;
    GenericAddressStructure X_PM1bControlBlock;
    GenericAddressStructure X_PM2ControlBlock;
    GenericAddressStructure X_PMTimerBlock;
    GenericAddressStructure X_GPE0Block;
    GenericAddressStructure X_GPE1Block;
};



#define DYNAMIC_ARRAY_WITH_INLINE_STORAGE(name, type, inline_capacity)       \
    struct name {                                                            \
        type inline_storage[inline_capacity];                                \
        type *dynamic_storage;                                               \
        size_t dynamic_capacity;                                         \
        size_t size_including_inline;                                    \
    };                                                                       \



#endif /*_ALINIX_KERNEL_KERNEL_H__*/