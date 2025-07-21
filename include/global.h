#ifndef __NOVANIX_KERNEL_GLOBAL_H
#define __NOVANIX_KERNEL_GLOBAL_H

#include <common/init.hpp>
#include <software/faccess.h>

/**
 * NOTE: JUST DEFINE THE GLOBAL VARIABLES AS "extern"
 */
extern file_t files[MAX_FILES];
extern INTEGER i_file;

#endif /*__NOVANIX_KERNEL_GLOBAL_H*/
