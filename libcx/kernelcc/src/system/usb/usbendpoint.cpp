#include <system/usb/usbendpoint.h>
#include <typing.hpp>

using namespace Novanix;
using namespace Novanix::common;
using namespace Novanix::system;

USBEndpoint::USBEndpoint(struct ENDPOINT_DESC* src)
{
    this->endpointNumber = src->end_point & 0xF;
    this->dir = (src->end_point & (1<<7)) ? EndpointDirection::In : EndpointDirection::Out;
    this->type = (EndpointType)(src->bm_attrbs & 0b11);
    this->maxPacketSize = src->max_packet_size;
    this->interval = src->interval;
}

BOOL USBEndpoint::Toggle()
{
    this->toggleState = !this->toggleState;
    return !this->toggleState; // Return original value
}

VOID USBEndpoint::SetToggle(BOOL v)
{
    this->toggleState = v;
}