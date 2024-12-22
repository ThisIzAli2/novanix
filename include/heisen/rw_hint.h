#ifndef _HEISEN_RW_HINT_H
#define _HEISEN_RW_HINT_H

#include <heisen/build_bug.h>
#include <heisen/compiler_attributes.h>
#include <uapi/heisen/fcntl.h>

/* Block storage write lifetime hint values. */
enum rw_hint {
	WRITE_LIFE_NOT_SET	= RWH_WRITE_LIFE_NOT_SET,
	WRITE_LIFE_NONE		= RWH_WRITE_LIFE_NONE,
	WRITE_LIFE_SHORT	= RWH_WRITE_LIFE_SHORT,
	WRITE_LIFE_MEDIUM	= RWH_WRITE_LIFE_MEDIUM,
	WRITE_LIFE_LONG		= RWH_WRITE_LIFE_LONG,
	WRITE_LIFE_EXTREME	= RWH_WRITE_LIFE_EXTREME,
} __packed;

/* Sparse ignores __packed annotations on enums, hence the #ifndef below. */
#ifndef __CHECKER__
static_assert(sizeof(enum rw_hint) == 1);
#endif

#endif /* _HEISEN_RW_HINT_H */