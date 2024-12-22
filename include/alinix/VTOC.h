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
 * @file VTOC.h
 * @abstraction:
 *  VTOC filesystem header file.
*/
#ifndef __ALINIX_KERNEL_V_TOC_H
#define __ALINIX_KERNEL_V_TOC_H


#include <alinix/types.h>

/**
 * @brief VTOC file system structure implemented.
*/
struct DSCB1{
    unsigned char * ds1fmtid;
    uint16_t ds1dsnam;
    uint16_t start_cc;
    uint16_t start_hh;

};

void GetCHRFromVTOC(void *buffer);
void CheckDSCB(struct DSCB1 *dscb, const char *name);
void FindFile(const char *name) ;

#endif /*__ALINIX_KERNEL_V_TOC_H*/