/**
 * @author Ali Mirmohammad
 * @file listingcontroller.cpp
 * @credits Remco123
 ** This file is part of Novanix.

**Novanix is free software: you can redistribute it and/or modify
**it under the terms of the GNU Affero General Public License as published by
**the Free Software Foundation, either version 3 of the License, or
**(at your option) any later version.

**Novanix is distributed in the hope that it will be useful,
**but WITHOUT ANY WARRANTY; without even the implied warranty of
**MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
**GNU Affero General Public License for more details.

**You should have received a copy of the GNU Affero General Public License
**along with Novanix. If not, see <https://www.gnu.org/licenses/>.
*/
#include <system/listings/listingcontroller.h>
#include <system/system.h>
#include <typing.hpp>

using namespace Novanix;
using namespace Novanix::common;
using namespace Novanix::core;
using namespace Novanix::system;

ListingController::ListingController()
: waitingQueue(), currentReqThread(), requestBusy(false) {}

INTEGER ListingController::BeginListing(Thread* thread, uint32_t arg1) {
    Log(Error, "ListingController Class is used directly while it is virtual");
    return 0;
}
INTEGER ListingController::GetEntry(Thread* thread, INTEGER entry, uint32_t bufPtr) {
    Log(Error, "ListingController Class is used directly while it is virtual");
    return 0;
}
VOID ListingController::EndListing(Thread* thread) { 
    Log(Error, "ListingController Class is used directly while it is virtual");
}