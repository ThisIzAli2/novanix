/**
 * @author Ali Mirmohammad
 * @file serialport.h
 * *************************************IMPORTANT ALINIX LICENSE TERM********************************************
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
 * @abstraction:
 *  - Kernel serial ports implementations in header file.
*/

#ifndef _ALINIX_KERNEL_SERIAL_PORT_H__
#define _ALINIX_KERNEL_SERIAL_PORT_H__

#include <alinix/enums.h>
#include <alinix/types.h>

int SerialportSerialSendReady();

void SerialportWrite(char a);

void SerialportWriteStr(char * str);

// bool Initialized = false;
void WriteStr(char* str);


void SerialportInit(enum COMPort port);

void Writestr(char* s);
void Init(enum COMPort port);
uint32_t GetMSSinceBoot();
// static bool Initialized = false;

#endif  /*_ALINIX_KERNEL_SERIAL_PORT_H__*/