#ifndef __VDSO_TIME_H
#define __VDSO_TIME_H

#include <uapi/heisen/types.h>
#include <heisen/typing.h>
struct timens_offset {
	s64	sec;
	u64	nsec;
};

#endif /* __VDSO_TIME_H */