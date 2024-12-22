#ifndef __ALINIX_KERNEL_SYSTEM_DRIVERS_USB_USB_MOUSE_HPP
#define __ALINIX_KERNEL_SYSTEM_DRIVERS_USB_USB_MOUSE_HPP

#include <system/drivers/hidparser.hpp>
#include <system/drivers/usb/usbdevice.hpp>

class USBMouse : public USBDriver
{
private:
    HIDParser hidParser;
    bool GetHIDProperty(struct HID_DATA* target, uint8_t* buffer, int bufLen, HID_USAGE item);

    bool useCustomReport = false;
    struct HID_DATA hidX;
    struct HID_DATA hidY;
    struct HID_DATA hidZ;
    USBMouse* device;
    USBMouse* controller;
    uint8_t* hidDescriptor = 0;


    int InInterruptEndpoint = -1;
public:
    // Instance initializer
    USBMouse(USBDevice* dev);
    
    // Called when device is plugged into system
    bool Initialize();

    // Called when device is unplugged from system
    void DeInitialize();

    // Called by USB driver when we receive a interrupt packet
    bool HandleInterruptPacket(InterruptTransfer* transfer);
};

#endif /*__ALINIX_KERNEL_SYSTEM_DRIVERS_USB_USB_MOUSE_HPP*/