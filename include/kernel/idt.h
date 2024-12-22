#ifndef _HEISEN_IDT_H
#define _HEISEN_IDT_H

#include <heisen/typing.h>

extern void initIdt();
extern void SetIdtEntry(unsigned char num, size_t handler, unsigned short sel,
                        unsigned char flags);

// Marks the interrupt handler as entered. This is already called for you for
// interrupt handlers registered with InstallHardwareInterruptHandler.
extern void MarkInterruptHandlerAsEntered();

// Marks the interrupt handler as left. This is already called for you for
// interrupt handlers registered with InstallHardwareInterruptHandler.
extern void MarkInterruptHandlerAsLeft();

#endif // _HEISEN_IDT_H