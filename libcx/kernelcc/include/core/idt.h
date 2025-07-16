/**
 * @author Ali Mirmohammad
 * @file idt.h
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
#ifndef __Novanix__CORE__IDT_H
#define __Novanix__CORE__IDT_H

#include <common/types.h>
#include <core/port.h>
#include <core/registers.h>
#include <core/exceptions.h>
#include <system/bootconsole.h>
#include <common/convert.h>
#include <common/memoryoperations.h>
#include <system/interruptmanager.h>

namespace Novanix
{
    namespace core
    {
        #define IDT_ENTRY_SIZE 256
        #define IDT_PRESENT 0x80
        #define IDT_INTERRUPT 0xE
        #define IDT_INTERRUPT_OFFSET 0x20

        struct IDTEntry
        {
            common::uint16_t handlerLowBits;
            common::uint16_t selector;
            common::uint8_t reserved;
            common::uint8_t access;
            common::uint16_t handlerHighBits;
        } __attribute__((packed));

        struct IDTPointer
        {
            common::uint16_t size;
            common::uint32_t base;
        } __attribute__((packed));

        extern "C" void IgnoreInterrupt();
        extern "C" void HandleInterruptRequest0x00();
        extern "C" void HandleInterruptRequest0x01();
        extern "C" void HandleInterruptRequest0x02();
        extern "C" void HandleInterruptRequest0x03();
        extern "C" void HandleInterruptRequest0x04();
        extern "C" void HandleInterruptRequest0x05();
        extern "C" void HandleInterruptRequest0x06();
        extern "C" void HandleInterruptRequest0x07();
        extern "C" void HandleInterruptRequest0x08();
        extern "C" void HandleInterruptRequest0x09();
        extern "C" void HandleInterruptRequest0x0A();
        extern "C" void HandleInterruptRequest0x0B();
        extern "C" void HandleInterruptRequest0x0C();
        extern "C" void HandleInterruptRequest0x0D();
        extern "C" void HandleInterruptRequest0x0E();
        extern "C" void HandleInterruptRequest0x0F();
        extern "C" void HandleInterruptRequest0x31();

        extern "C" void HandleInterruptRequest0xDD();
        extern "C" void HandleInterruptRequest0x60();

        extern "C" void HandleException0x00();
        extern "C" void HandleException0x01();
        extern "C" void HandleException0x02();
        extern "C" void HandleException0x03();
        extern "C" void HandleException0x04();
        extern "C" void HandleException0x05();
        extern "C" void HandleException0x06();
        extern "C" void HandleException0x07();
        extern "C" void HandleException0x08();
        extern "C" void HandleException0x09();
        extern "C" void HandleException0x0A();
        extern "C" void HandleException0x0B();
        extern "C" void HandleException0x0C();
        extern "C" void HandleException0x0D();
        extern "C" void HandleException0x0E();
        extern "C" void HandleException0x0F();
        extern "C" void HandleException0x10();
        extern "C" void HandleException0x11();
        extern "C" void HandleException0x12();
        extern "C" void HandleException0x13();        

        class InterruptDescriptorTable
        {
        private:
            static void SetDescriptor(common::uint32_t number,  void (*handler)(), int accesLevel = 0);

            static common::uint32_t HandleInterrupt(CPUState* state);
        public:
            static void Install();

            static void EnableInterrupts();
            static void DisableInterrupts();
            static bool AreEnabled();
        };
    }
}

#endif