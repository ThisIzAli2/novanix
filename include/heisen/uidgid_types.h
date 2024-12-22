/* SPDX-License-Identifier: GPL-2.0 */
#ifndef _HEISEN_UIDGID_TYPES_H
#define _HEISEN_UIDGID_TYPES_H

#include <heisen/types.h>

typedef struct {
	uid_t val;
} kuid_t;

typedef struct {
	gid_t val;
} kgid_t;

#endif /* _HEISEN_UIDGID_TYPES_H */