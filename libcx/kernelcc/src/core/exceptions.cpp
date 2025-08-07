/**
 * @author Ali Mirmohammad
 * @file exceptions.cpp
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

#include <core/exceptions.h>
#include <system/system.h>
#include <common/print.h>
#include <alinix/security.h>
#include <typing.hpp>

using namespace Novanix;
using namespace Novanix::common;
using namespace Novanix::core;
using namespace Novanix::system;

// Should we try to automaticaly fix pagefaults?
BOOL autoFixPagefaults = false;

uint32_t Exceptions::DivideByZero(uint32_t esp)
{
    BootConsole::ForegroundColor = VGA_COLOR_RED;
    BootConsole::WriteLine("Got Divide by zero Exception");

    InterruptDescriptorTable::DisableInterrupts();

    BootConsole::WriteLine();

    #ifdef DEV
    Exceptions::ShowStacktrace(esp);
    #endif
    System::Init();
    return esp; // We don't get here
}
uint32_t Exceptions::GeneralProtectionFault(uint32_t esp)
{
    BootConsole::ForegroundColor = VGA_COLOR_RED;
    BootConsole::WriteLine("Got General Protection Fault Exception");

    CPUState* state = (CPUState*)esp;
    BootConsole::Write("EIP: 0x");
    Print::printfHex32(state->EIP);
    BootConsole::WriteLine();

    if(state->ErrorCode != 0)
    {
        SelectorErrorCode* error = (SelectorErrorCode*)&state->ErrorCode;
        BootConsole::Write("External: "); BootConsole::WriteLine(Convert::IntToString(error->External));
        BootConsole::Write("Table: "); BootConsole::WriteLine(Convert::IntToString(error->Table));
        BootConsole::Write("Index: "); BootConsole::WriteLine(Convert::IntToString(error->TableIndex));
    }

    InterruptDescriptorTable::DisableInterrupts();
    
    BootConsole::WriteLine();
    #ifdef DEV
    Exceptions::ShowStacktrace(esp);
    #endif
    System::Init();
    return esp; // We don't get here
}
uint32_t Exceptions::PageFault(uint32_t esp)
{
    #ifdef DEV
    BootConsole::ForegroundColor = VGA_COLOR_BROWN;

    InterruptDescriptorTable::DisableInterrupts();

    uint32_t errorAddress;
    asm volatile("mov %%cr2, %0" : "=r"(errorAddress));

    CPUState* regs = (CPUState*)esp;

    // The error code gives us details of what happened.
    INTEGER present   = !(regs->ErrorCode & 0x1); // Page not present
    INTEGER rw = regs->ErrorCode & 0x2;           // Write operation?
    INTEGER us = regs->ErrorCode & 0x4;           // Processor was in user-mode?
    INTEGER reserved = regs->ErrorCode & 0x8;     // Overwritten CPU-reserved bits of page entry?
    INTEGER id = regs->ErrorCode & 0x10;          // Caused by an instruction fetch?

    BootConsole::Write("Got Page Fault (");
    kernelMemoryCorruptionLockDown();

    if(present)
        BootConsole::Write("present ");
    if(rw)
        BootConsole::Write("read-only ");
    if(us)
        BootConsole::Write("user-mode ");
    if(reserved)
        BootConsole::Write("reserved ");
    if(id)
        BootConsole::Write("instruction fetch ");

    BootConsole::Write(") at 0x");
    Print::printfHex32(errorAddress);
    BootConsole::Write(" EIP: 0x");
    Print::printfHex32(regs->EIP);

    BootConsole::Write(" Memory Intact: ");
    if(KernelHeap::CheckForErrors())
        BootConsole::Write(" No ");
    else
        BootConsole::Write(" Yes ");
    
    if(System::scheduler != 0 && System::scheduler->CurrentProcess() != 0 && System::scheduler->CurrentProcess()->fileName != 0) {
        BootConsole::Write(" Process: ");
        BootConsole::WriteLine(System::scheduler->CurrentProcess()->fileName);
    }

    if(autoFixPagefaults && present) //Identity map error address
    {
        LPVOID ptr = (LPVOID)errorAddress;
        VirtualMemoryManager::mapVirtualToPhysical(ptr, ptr, true, true); //Readonly is probably a good idea        
        
        BootConsole::WriteLine(" Fixed pagefault");
        return esp;
    }
    BootConsole::WriteLine();
    #ifdef DEV
    Exceptions::ShowStacktrace(esp);
    #endif
    System::Init();
    return esp; // We don't get here
    #endif // DEV
}

uint32_t Exceptions::TrapException(uint32_t esp)
{
    BootConsole::WriteLine("Got Trap Exception");
    BootConsole::Write("Next Instruction at: 0x"); Print::printfHex32(((CPUState*)esp)->EIP); BootConsole::WriteLine();

    return esp;
}

uint32_t Exceptions::FloatingPointException(uint32_t esp)
{
    BootConsole::WriteLine("Got SIMD Floating-Point Exception");
    uint32_t mxcsr;
    asm volatile ("stmxcsr %0":"=m" (mxcsr));
    BootConsole::Write("mxcsr: 0b"); Print::printbits(mxcsr); BootConsole::WriteLine();
    BootConsole::Write("Instruction Pointer: 0x"); Print::printfHex32(((CPUState*)esp)->EIP); BootConsole::WriteLine();

    InterruptDescriptorTable::DisableInterrupts();

    BootConsole::WriteLine();
    #ifdef DEV
    Exceptions::ShowStacktrace(esp);
    #endif
    System::Init();
    return esp; // We don't get here
}
uint32_t Exceptions::StackSegmentFault(uint32_t esp)
{
    BootConsole::ForegroundColor = VGA_COLOR_RED;
    BootConsole::WriteLine("Got Stack Segment Fault Exception");

    CPUState* state = (CPUState*)esp;
    BootConsole::Write("Instruction Pointer: 0x"); Print::printfHex32(((CPUState*)esp)->EIP); BootConsole::WriteLine();

    if(state->ErrorCode != 0)
    {
        SelectorErrorCode* error = (SelectorErrorCode*)&state->ErrorCode;
        BootConsole::Write("External: "); BootConsole::WriteLine(Convert::IntToString(error->External));
        BootConsole::Write("Table: "); BootConsole::WriteLine(Convert::IntToString(error->Table));
        BootConsole::Write("Index: "); BootConsole::WriteLine(Convert::IntToString(error->TableIndex));
    }

    InterruptDescriptorTable::DisableInterrupts();
    BootConsole::WriteLine();
    #ifdef DEV
    Exceptions::ShowStacktrace(esp);
    #endif
    System::Init();
    return esp; // We don't get here
}

uint32_t Exceptions::HandleException(uint32_t number, uint32_t esp)
{
    switch(number)
    {
        case 0:
            return DivideByZero(esp);
        case 0xD:
            return GeneralProtectionFault(esp);
        case 0xE:
            return PageFault(esp);
        case 0x1:
            return TrapException(esp);
        case 0xC:
            return StackSegmentFault(esp);
        case 0x13:
            return FloatingPointException(esp);
        default:
            {
                BootConsole::ForegroundColor = VGA_COLOR_RED;
                BootConsole::Write("Unhandled exception: "); BootConsole::WriteLine(Convert::IntToString(number));
                BootConsole::WriteLine("Halting System");
                BootConsole::Write("Instruction Pointer: 0x"); Print::printfHex32(((CPUState*)esp)->EIP); BootConsole::WriteLine();
                System::Init();
            }
    }
    return esp;
}

VOID Exceptions::EnablePagefaultAutoFix()
{
    autoFixPagefaults = true;
}
VOID Exceptions::DisablePagefaultAutoFix()
{
    autoFixPagefaults = false;
}

VOID Exceptions::ShowStacktrace(common::uint32_t esp)
{
    Log(Info, "---------- Stacktrace -----------");
    if(System::scheduler != 0 && System::scheduler->CurrentProcess() != 0) {
        Process* curProc = System::scheduler->CurrentProcess();
        #if ENABLE_ADV_DEBUG
        if(curProc->symDebugger)
            curProc->symDebugger->Stacktrace((CPUState*)esp);
        #else
        System::kernelDebugger->Stacktrace((CPUState*)esp);
        #endif
    }
}