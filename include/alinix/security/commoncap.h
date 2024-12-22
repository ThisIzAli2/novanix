/**
 * @file commoncap.h
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
 *  - Security util.
*/
#ifndef __ALINIX_KERNEL_SECURITY_COMMON_CAP_H
#define __ALINIX_KERNEL_SECURITY_COMMON_CAP_H


int cap_capable(int cap, unsigned int opts);
// int cap_ptrace_access_check(struct task_struct *child, unsigned int mode);
#endif /*__ALINIX_KERNEL_SECURITY_COMMON_CAP_H*/