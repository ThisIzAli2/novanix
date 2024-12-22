/**
 * @author Ali Mirmohammad
 * @file nmi.h
 * *************************************IMPORTANT ALINIX LICENSE TERM********************************************
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
 *  - Kernel NMI header file implemented.
*/
#ifndef __ALINIX_KERNEL_NMI_H
#define __ALINIX_KERNEL_NMI_H


#define NMI_PORT 0x70

void NMI_enable(); // Enable EMI 
void NMI_disable(); // Disable NMI

#endif /*__ALINIX_KERNEL_NMI_H*/