#ifndef HAL_H
#define HAL_H

#include <drivers/ata.h>
#include <drivers/cpu.h>
#include <drivers/dma.h>
#include <hal/device.h>
#include <hal/exception.h>
#include <drivers/floppy.h>
#include <hal/gdt.h>
#include <hal/idt.h>
#include <hal/syscall.h>
#include <hal/tss.h>
#include <drivers/io.h>
#include <drivers/keyboard.h>
#include <mm/memory.h>
#include <drivers/pic.h>
#include <drivers/pit.h>
#include <types.h>

extern uint32_t kernel_start;
extern uint32_t kernel_end;

void hal_init();
void sleep(int s);
void reboot();

#endif