/**
 * @author Ali Mirmohammad
 * @file cpu_mask.h
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
 *  - Implements kernel CPU mask in header file.
*/
#ifndef __ALINIX_KERNEL_CPU_MASK_H
#define __ALINIX_KERNEL_CPU_MASK_H


#define CONFIG_NR_CPUS	1

/* Places which use this should consider cpumask_var_t. */
#define NR_CPUS		CONFIG_NR_CPUS


/**
 * @brief Data structure for the CPU mask util.
 * @brief Useful for bit ops.
*/
typedef struct cpumask { char bits; } cpumask_t;


#endif /*__ALINIX_KERNEL_CPU_MASK_H*/