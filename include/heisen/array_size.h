#ifndef _HEISEN_ARRAY_SIZE_H
#define _HEISEN_ARRAY_SIZE_H

#include <heisen/compiler.h>

/**
 * ARRAY_SIZE - get the number of elements in array @arr
 * @arr: array to be sized
 */
#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof((arr)[0]) )

#endif  /* _HEISEN_ARRAY_SIZE_H */