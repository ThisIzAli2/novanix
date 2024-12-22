/**
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

#ifndef SCHED_H
#define SCHED_H

#include <proc/proc.h>

process_t *get_cur_proc();
process_t *get_proc_by_id(int id);
uint32_t schedule(uint32_t esp);
void sched_add_proc(process_t *proc);
void sched_remove_proc(int id);
void sched_init();
int get_nproc();
void print_procs();

#endif