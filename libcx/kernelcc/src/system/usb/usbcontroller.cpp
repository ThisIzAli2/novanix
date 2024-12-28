#include <system/usb/usbcontroller.h>
#include <system/drivers/usb/usbdefs.h>
#include <system/system.h>
#include <typing.hpp>

using namespace Novanix;
using namespace Novanix::common;
using namespace Novanix::core;
using namespace Novanix::system;
using namespace Novanix::system::drivers;

USBController::USBController(USBControllerType usbType)
{
    this->type = usbType;
    this->interrupTransfers.Clear();
}

VOID USBController::Setup()
{
    Log(Error, "Virtual function called directly %s:%d", __FILE__, __LINE__);
}
VOID USBController::ControllerChecksThread()
{
    Log(Error, "Virtual function called directly %s:%d", __FILE__, __LINE__);
}

//////////////
// Controller specific transfer functions
//////////////

BOOL USBController::BulkIn(USBDevice* device, VOID* retBuffer, INTEGER len, INTEGER endP)
{
    Log(Error, "Virtual function called directly %s:%d", __FILE__, __LINE__);
    return false;
}
BOOL USBController::BulkOut(USBDevice* device, VOID* sendBuffer, INTEGER len, INTEGER endP)
{
    Log(Error, "Virtual function called directly %s:%d", __FILE__, __LINE__);
    return false;
}
BOOL USBController::ControlIn(USBDevice* device, VOID* target, const INTEGER len, const uint8_t requestType, const uint8_t request, const uint16_t valueHigh, const uint16_t valueLow, const uint16_t index)
{
    Log(Error, "Virtual function called directly %s:%d", __FILE__, __LINE__);
    return false;
}
BOOL USBController::ControlOut(USBDevice* device, const INTEGER len, const uint8_t requestType, const uint8_t request, const uint16_t valueHigh, const uint16_t valueLow, const uint16_t index)
{
    Log(Error, "Virtual function called directly %s:%d", __FILE__, __LINE__);
    return false;
}
VOID USBController::InterruptIn(USBDevice* device, INTEGER len, INTEGER endP)
{
    Log(Error, "Virtual function called directly %s:%d", __FILE__, __LINE__);
}


/////////////
// Specific Functions independent of controller
/////////////


BOOL USBController::GetDeviceDescriptor(struct DEVICE_DESC* dev_desc, USBDevice* device)
{
    return ControlIn(device, dev_desc, sizeof(struct DEVICE_DESC), STDRD_GET_REQUEST, DeviceRequest::GET_DESCRIPTOR, DescriptorTypes::DEVICE);
}

BOOL USBController::GetStringDescriptor(struct STRING_DESC* stringDesc, USBDevice* device, uint16_t index, uint16_t lang)
{
    if(!ControlIn(device, stringDesc, 2, STDRD_GET_REQUEST, DeviceRequest::GET_DESCRIPTOR, DescriptorTypes::STRING, index, lang))
        return false;
        
    INTEGER totalSize = stringDesc->len;
    return ControlIn(device, stringDesc, totalSize, STDRD_GET_REQUEST, DeviceRequest::GET_DESCRIPTOR, DescriptorTypes::STRING, index, lang);
}

uint8_t* USBController::GetConfigDescriptor(USBDevice* device)
{
    struct CONFIG_DESC confDesc;
    MemoryOperations::memset(&confDesc, 0, sizeof(struct CONFIG_DESC));

    if(!ControlIn(device, &confDesc, sizeof(struct CONFIG_DESC), STDRD_GET_REQUEST, GET_DESCRIPTOR, CONFIG))
        return 0;
    
    INTEGER totalSize = confDesc.tot_len;
    uint8_t* buffer = new uint8_t[totalSize];
    MemoryOperations::memset(buffer, 0, totalSize);

    if(!ControlIn(device, buffer, totalSize, STDRD_GET_REQUEST, GET_DESCRIPTOR, CONFIG))
        return 0;
    
    return buffer;
}

BOOL USBController::SetConfiguration(USBDevice* device, uint8_t config)
{
    return ControlOut(device, 0, STDRD_SET_REQUEST, SET_CONFIGURATION, 0, config);
}

INTEGER USBController::GetConfiguration(USBDevice* device)
{
    uint8_t ret = 0;
    if(!ControlIn(device, &ret, 1, STDRD_GET_REQUEST, GET_CONFIGURATION))
        return 0;
    
    return ret;
}

INTEGER USBController::GetMaxLuns(USBDevice* device)
{
    uint8_t ret = 0;
    for(INTEGER i = 0; i < 3; i++) {
        if(ControlIn(device, &ret, 1, DEV_TO_HOST | REQ_TYPE_CLASS | RECPT_INTERFACE, GET_MAX_LUNS))
            return ret;
        
        // If request failed send Clear feature (HALT) to control endpoint
        device->controller->ControlOut(device, 0, HOST_TO_DEV | REQ_TYPE_STNDRD | RECPT_ENDPOINT, CLEAR_FEATURE);
    }
    return 0;
}