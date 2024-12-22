/**
 * @author Ali Mirmohammad
 * @file apm.h
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

/**
 * @abstract:
 *  - Kernel APM implemented.
*/

#ifndef __ALINIX_KERNEL_APM_H
#define __ALINIX_KERNEL_APM_H

#include <alinix/system/component.h>
#include <alinix/types.h>


#define APM_SIGNATURE           0x504D //"PM"
#define APM_ALL_DEVICE          ((uint16_t) 0x0001)
#define APM_DEVICE_DISPLAY      ((uint16_t) 0x0100)
#define APM_DEVICE_STORAGE      ((uint16_t) 0x0200)
#define APM_DEVICE_PARRALEL     ((uint16_t) 0x0300)
#define APM_DEVICE_SERIAL       ((uint16_t) 0x0400)
#define APM_DEVICE_NETWORK      ((uint16_t) 0x0500)
#define APM_DEVICE_PCMCIA       ((uint16_t) 0x0600)
#define APM_DEVICE_ALL          ((uint16_t) 0x00FF)

#define APM_POWER_STANDBY       0x01
#define APM_POWER_SUSPEND       0x02
#define APM_POWER_OFF           0x03
#define APM_POWER_PROCESSING    0x04
#define APM_POWER_REJECT        0x05

#define APM_FUNC_INSTALL_CHECK                      0x00
#define APM_FUNC_CONNECT_REALMODE                   0x01
#define APM_FUNC_CONNECT_16                         0x02
#define APM_FUNC_CONNECT_32                         0x03
#define APM_FUNC_DISCONNECT                         0x04
#define APM_FUNC_CPU_IDLE                           0x05
#define APM_FUNC_CPU_BUSY                           0x06
#define APM_FUNC_SET_POWER_STATE                    0x07
#define APM_FUNC_ENABLE_POWER_MANAGEMENT            0x08
#define APM_FUNC_RESTORE_DEFAULTS                   0x09
#define APM_FUNC_GET_POWER_STATUS                   0x0A
#define APM_FUNC_GET_PM_EVENT                       0x0B
#define APM_FUNC_GET_POWER_STATE                    0x0C
#define APM_FUNC_SET_DEV_POWER_MANAGEMENT           0x0D
#define APM_FUNC_DRIVER_VERSION                     0x0E
#define APM_FUNC_ENGAGE_DISENGAGE_POWER_MANAGEMENT  0x0F
#define APM_FUNC_GET_CABABILITIES                   0x10
#define APM_FUNC_SET_RESUME_TIMER                   0x11
#define APM_FUNC_SET_RESUME_RING                    0x12
#define APM_FUNC_SET_TIMER_BASED_REQ                0x13
#define APM_FUNC_OEM   



char* GetComponentName(SystemComponent* component);

char* GetComponentDescription(SystemComponent* component) ;
typedef struct APMController {
    SystemComponent base;
    int Enabled;
} APMController;

APMController* APMController_create();

void CheckAndHandleEvents(APMController* controller);

void SetPowerState(APMController* controller, unsigned short device, unsigned char state);

void DisableResumeTimer(APMController* controller) ;

void DisableRingIndicator(APMController* controller);


#endif // __ALINIX_KERNEL_APM_H