#ifndef _HEISEN_ERRNAME_H
#define _HEISEN_ERRNAME_H

#include <heisen/stddef.h>


#ifdef CONFIG_SYMBOLIC_ERRNAME
const char *errname(int err);
#else
static inline const char *errname(int err)
{
	return NULL;
}
#endif

#endif /* _HEISEN_ERRNAME_H */