/**
 * @author Ali Mirmohammad
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
 * @file cpu.h
 * Abstraction:
 *      - Provides the CPU  architecture information.
 *      - Macros related to the  CPU architecture are defined here.
*/

#ifndef __ALINIX_KERNEL_CPU_H
#define __ALINIX_KERNEL_CPU_H

#include <alinix/types.h>
#include <alinix/device.h>

#define EDX_SSE2 (1 << 26) // Streaming SIMD Extensions 2
#define EDX_FXSR (1 << 24) // Can we use the fxsave/fxrstor instructions?


/*This function will print the CPU vendor*/
void PrintCpuVendor();

/*Initiate the CPU*/
void enableCpuFeatures();


/////////////////////
/// @brief ////////
//////////////////////
// Defining the CPU informations for kernel drivers
struct cpu{
    int node_id;
    int hotpluggable;
    struct device dev;
};

//////////////////////
// Defining the cpu info structure which contains all information about the CPU

EXTERNAL VOID boot_cpu_init(NO_ARGS);
EXTERNAL VOID boot_hotplug_init(NO_ARGS);
EXTERNAL VOID cpu_init(NO_ARGS);
EXTERNAL VOID trap_init(NO_ARGS);
EXTERNAL NUMBER register_cpu(struct cpu *cpu,int num);
EXTERNAL struct device *get_cpu_device(POSITIVE cpu);
EXTERNAL bool cpu_is_hotplfuggable(POSITIVE cpu);
EXTERNAL bool arch_match_cpu_phys_id(NUMBER cpu,uint64_t phys_id);
EXTERNAL bool arch_find_n_match_cpu_physical_id(struct device_node *cpun,NUMBER cpu,POSITIVE thread);
EXTERNAL NUMBER cpu_add_dev_attr(struct device_attribute *attr);
EXTERNAL VOID cpu_remove_dev_attr(struct device_attribute *attr);





#endif /*__ALINIX_KERNEL_CPU_H*/