/**
 * @file consumer.h
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
#ifndef __ALINIX_KERNEL_IIO_CONSUMER_H
#define __ALINIX_KERNEL_IIO_CONSUMER_H


#include <alinix/types.h>
#include <alinix/device.h>

struct iio_dev;
struct iio_chan_spec;
struct device;
struct fwnode_handle;


struct iio_dev{
    int     modes;
    struct device dev;
    struct iio_buffer		*buffer;
    CONSTANT unsigned long *available_scan_masks;
    unsigned mask_length;
    const unsigned long		*active_scan_mask;
    bool scanTimeStamp;
    
};



#endif // __ALINIX_KERNEL_IIO_CONSUMER_H