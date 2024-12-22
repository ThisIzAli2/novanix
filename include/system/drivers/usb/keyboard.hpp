#ifndef __ALINIX_KERNEL_SYSTEM_DRIVER_USB_KEYBOARD_HPP
#define __ALINIX_KERNEL_SYSTEM_DRIVER_USB_KEYBOARD_HPP


#ifndef __cplusplus
# error "This file must be compiled with C++"

#endif  /* !__cplusplus */

#include <alinix/keyboard.h>
#include <alinix/types.h>

class Keyboard
{
public:
    KeyboardType type;
    InternalKeyboardStatus status;
public:
    Keyboard(KeyboardType type);

    // Update LED's on a keyboard device
    virtual void UpdateLEDS();
    
    // Checks if the buffer contains the given key, also returns position of key
    bool ContainsKey(uint8_t key, uint8_t* packet, int* pos);
};

#endif //__ALINIX_KERNEL_SYSTEM_DRIVER_USB_KEYBOARD_HPP