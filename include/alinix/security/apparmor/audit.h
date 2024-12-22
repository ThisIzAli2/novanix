/**
 * @file audit.h
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
 * 	- Implements the security audits for the kernel.
*/
#ifndef __ALINIX_KRL_SECURITY_APP_ARMOR_H
#define __ALINIX_KRL_SECURITY_APP_ARMOR_H


#define AA_CLASS_X		31
#define AA_CLASS_DBUS		32

#define AA_CLASS_LAST		AA_CLASS_DBUS

#include <alinix/types.h>

struct apparmor_audit_data {
    int error;
    int type;
    u16 cls;
    const char* op;
    const char *name;
	const char *info;
	u32 request;
	u32 denied;
    union {
        		/* these entries require a custom callback fn */
		struct {
			struct aa_label *peer;
			union {
				struct {
					const char *target;
					int ouid;
				} fs;
				struct {
					int rlim;
					unsigned long max;
				} rlim;
				struct {
					int signal;
					int unmappedsig;
				};
				struct {
					int type, protocol;
					// struct sock *peer_sk;
					void *addr;
					int addrlen;
				} net;
			};
		};
		struct {
			// struct aa_profile *profile;
			const char *ns;
			long pos;
		} iface;
		struct {
			const char *src_name;
			const char *type;
			const char *trans;
			const char *data;
			unsigned long flags;
		} mnt;
		struct {
			struct aa_label *target;
		} uring;
	};
};



#endif // __ALINIX_KRL_SECURITY_APP_ARMOR_H