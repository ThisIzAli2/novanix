#include <system/listings/listingcontroller.h>
#include <system/system.h>

using namespace Novanix;
using namespace Novanix::common;
using namespace Novanix::core;
using namespace Novanix::system;

ListingController::ListingController()
: waitingQueue(), currentReqThread(), requestBusy(false) {}

int ListingController::BeginListing(Thread* thread, uint32_t arg1) {
    Log(Error, "ListingController Class is used directly while it is virtual");
    return 0;
}
int ListingController::GetEntry(Thread* thread, int entry, uint32_t bufPtr) {
    Log(Error, "ListingController Class is used directly while it is virtual");
    return 0;
}
void ListingController::EndListing(Thread* thread) { 
    Log(Error, "ListingController Class is used directly while it is virtual");
}