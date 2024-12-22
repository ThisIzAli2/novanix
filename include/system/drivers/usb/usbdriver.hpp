#ifndef __ALINIX_KERNEL_USB_DRIVER_SYSTEM_HPP
#define __ALINIX_KERNEL_USB_DRIVER_SYSTEM_HPP


// #include <system/drivers/driver.h>
#include <system/drivers/driver.hpp>
#include <system/drivers/usb/usbdevice.hpp>
#include <alinix/list.hpp>


// typedef  InterruptTransfer InterruptTransfer ;


class USBDriver {
public:
    uint8_t device;
    // Constructor
    USBDriver(class USBDevice* dev, char* driverName);
 
    // Destructor
    ~USBDriver();

    // Other member functions
    void DeInitialize();
    bool HandleInterruptPacket(struct InterruptTransfer* transfer);
    // static USBDevice* device; // Pointer to USBDevice
};





#endif /*__ALINIX_KERNEL_USB_DRIVER_SYSTEM_HPP*/