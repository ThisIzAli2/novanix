/**
 * @author Ali Mirmohammad
 * @file usbendpoint.cpp
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