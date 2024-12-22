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
 * @file device.h
 * Abstraction:
 *      - Device  (CPU / GPU) utility
*/


#ifndef __ALINIX_KERNEL_DEVICE_H
#define __ALINIX_KERNEL_DEVICE_H

#include <alinix/types.h>
#include <alinix/kobject.h>

struct device_private;

struct device{
	struct kobject kobj;
    CONSTANT char *name;        
    uint64_t base;
    CONSTANT char vendor;   /* Vendor name */
    CONSTANT char product;   /* Product name */
    struct dev_pm_domain	*pm_domain;
    struct device_private	*p;
};


struct device_dma_parameters {
	/*
	 * a low level driver may set these to teach IOMMU code about
	 * sg limitations.
	 */
	unsigned int max_segment_size;
	unsigned int min_align_mask;
	unsigned long segment_boundary_mask;
};

#endif /*__ALINIX_KERNEL_DEVICE_H*/