/**
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
#ifndef __ALINIX_KERNEL_NET_IPDEF_H
#define __ALINIX_KERNEL_NET_IPDEF_H


#include <alinix/types.h>
#include <net/err.h>

struct ip_addr {
    uint32_t addr;
};

struct ip_addr_packed {
    uint32_t addr;
};

// Define the typedefs
typedef struct ip_addr ip_addr_t;
typedef struct ip_addr_packed ip_addr_p_t;

typedef err_t *netif_init_fn;

typedef err_t *netif_input_fn;

typedef err_t *netif_output_fn;


typedef err_t *netif_linkoutput_fn;

#endif