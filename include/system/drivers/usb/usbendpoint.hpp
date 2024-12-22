#ifndef __ALINIX_KERNEL_SYSTEM_DRIVERS_USB_USB_ENDPOINT
#define __ALINIX_KERNEL_SYSTEM_DRIVERS_USB_USB_ENDPOINT

#include <alinix/types.h>

// enum EndpointDirection : int
// {
//     Out,
//     In
// };

// enum EndpointType : int
// {
//     Control,
//     Isochronous,
//     Bulk,
//     Interrupt
// };

// An easy interface for managing endpoints
class USBEndpoint
{
private:
    bool toggleState = false;
public:
    uint8_t endpointNumber = 0; // Index of endpoint in device
    EndpointDirection dir = EndpointDirection::Out; // Direction of transfer for this endpoint
    EndpointType type = EndpointType::Control; // Type of endpoint
    uint16_t maxPacketSize = 0; // Max size a packet can be for this endpoint
    uint8_t interval = 0; // Interval for interrupt packets
public:
    // Create new USB Endpoint from ENDPOINT_DESC gathered from configuration descriptor
    USBEndpoint(struct ENDPOINT_DESC* src);

    // Get toggle bit and toggle it for next packet
    bool Toggle();

    // Set Toggle bit
    void SetToggle(bool v);
};

#endif // __ALINIX_KERNEL_SYSTEM_DRIVERS_USB_USB_ENDPOINT