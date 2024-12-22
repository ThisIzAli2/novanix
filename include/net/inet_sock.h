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
#ifndef __ALINIX_KERNEL_INET_SOCK_H
#define __ALINIX_KERNEL_INET_SOCK_H

#include <alinix/types.h>

struct ip_options{
    uint32_t addr;
    uint32_t nexthop;
    unsigned char opt_len;
    unsigned char srr;
    unsigned char rr;
    unsigned char ts;
    unsigned char	is_strictroute:1,
			srr_is_hit:1,
			is_changed:1,
			rr_needaddr:1,
			ts_needtime:1,
			ts_needaddr:1;
    unsigned char	router_alert;
	unsigned char	cipso;
	// unsigned char	__pad2;
	// unsigned char	__data[];
};


struct ip_options_rcu {
	struct rcu_head rcu;
	struct ip_options opt;
};

struct ip_options_data {
	struct ip_options_rcu	opt;
    char			data[40];
};

#endif 