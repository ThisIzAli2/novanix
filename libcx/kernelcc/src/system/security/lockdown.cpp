/**
 * @file lockdown.cpp
 ** This file is part of AliNix.

**AliNix is KernelHeap::free software: you can redistribute it and/or modify
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
 * Abstraction:
 *  - Provides kernel lock down utility.
 *  - Used for C++.
*/

#include "loadpin.hpp"
#include "module.hpp"

#include <system/log.h>
#include <common/string.h>
#include <alinix/module.h>

using namespace CactusOS;
using namespace CactusOS::common;
using namespace CactusOS::system;


MODULE_AUTHOR("Ali Mirmohammad")
MODULE_DESCRIPTION("Kernel lock down implementation for security stuff")
MODULE_LICENSE("AGPL-3.0")
MODULE_VERSION("1.0")



static const enum lockdown_reason lockdown_levels[] = {LOCKDOWN_NONE,
						 LOCKDOWN_INTEGRITY_MAX,
						 LOCKDOWN_CONFIDENTIALITY_MAX};

static enum lockdown_reason kernel_locked_down;
static const char* lockdown_reasons;

// Needs for the lockdown reason


/**
 * @brief Locks down the kernel with a specified reason and lockdown level.
 *
 * This function logs an error message indicating that the kernel is being
 * locked down due to a specified reason, and then sets the global variable
 * `kernel_locked_down` to the specified lockdown level.
 *
 * @param where A string describing the reason for the lockdown. This string
 *              is included in the error message logged.
 * @param level An enum value representing the level of lockdown to apply.
 *
 * @return Returns 0 to indicate the operation was successful.
 */
static int lock_kernel_down(const char *where,enum lockdown_reason level){
    Log(Error,"Kernel is locked down due to the %s",where);
    kernel_locked_down = level;
    return 0;
}

/**
 * @brief Sets the kernel lockdown level based on the provided parameter.
 *
 * This function evaluates the provided `level` string to determine the
 * appropriate lockdown level to set. It supports two levels: "integrity"
 * and "confidentiality". If the level is "integrity", the kernel is locked
 * down to protect data from unauthorized modification, deletion, or disclosure.
 * If the level is "confidentiality", the kernel is locked down to protect
 * sensitive information from unauthorized access.
 *
 * @param level A string representing the desired lockdown level. Expected
 *              values are "integrity" or "confidentiality".
 *
 * @return Returns 0 on success. Returns -EINVAL if the `level` is NULL or
 *         not a recognized value.
 */
static int lockdown_param(char *level){
    if (!level){
        return -EINVAL;
    }
    if (String::strcmp(level,"integrity"))
        /*integrity refers to the protection of data from unauthorized modification, deletion, or disclosure. */
        lock_kernel_down("command line", LOCKDOWN_INTEGRITY_MAX);
    
    /*n the other hand, refers to the protection of sensitive information from unauthorized Access*/
    else if (String::strcmp(level, "confidentiality"))
		lock_kernel_down("command line", LOCKDOWN_CONFIDENTIALITY_MAX);
    
    else 
        return -EINVAL;
    
    return 0;
}


static int  lockdown_lsm_init(void){

#if defined(CONFIG_LOCK_DOWN_KERNEL_FORCE_INTEGRITY)
	lock_kernel_down("Kernel configuration", LOCKDOWN_INTEGRITY_MAX);
#elif defined(CONFIG_LOCK_DOWN_KERNEL_FORCE_CONFIDENTIALITY)
	lock_kernel_down("Kernel configuration", LOCKDOWN_CONFIDENTIALITY_MAX);
#endif
}


/////////////////////////////////////

void kernelMemoryCorruptionLockDown(){
    lock_kernel_down("Memory corruption",MEMORY_CORRUPTION);
}