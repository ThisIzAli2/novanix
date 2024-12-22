/**
 * @file listingcontroller.h
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

#ifndef _ALINIX_KERNEL_LISTING_CONTROLLER_H
#define _ALINIX_KERNEL_LISTING_CONTROLLER_H

#include <alinix/types.h>

struct Thread* currentReqThread;

bool requestBusy = false;

int BeginListing(Thread* thread, uint32_t arg1);
int GetEntry(Thread* thread, int entry, uint32_t bufPtr);
void EndListing(Thread* thread);

#endif /*_ALINIX_KERNEL_LISTING_CONTROLLER_H*/