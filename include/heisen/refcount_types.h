#ifndef _HEISEN_REFCOUNT_TYPES_H
#define _HEISEN_REFCOUNT_TYPES_H

#include <heisen/types.h>

/**
 * typedef refcount_t - variant of atomic_t specialized for reference counts
 * @refs: atomic_t counter field
 *
 * The counter saturates at REFCOUNT_SATURATED and will not move once
 * there. This avoids wrapping the counter and causing 'spurious'
 * use-after-free bugs.
 */
typedef struct refcount_struct {
	atomic_t refs;
} refcount_t;

#endif /* _HEISEN_REFCOUNT_TYPES_H */