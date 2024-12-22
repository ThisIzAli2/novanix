#ifndef _HEISEN_HWIO_KERNEL_INCLUDE_H
#define _HEISEN_HWIO_KERNEL_INCLUDE_H

#include <heisen/typing.h>

enum IO_GETKEY_WAIT_MODE {
    IO_GETKEY_WAITMODE_NOWAIT = 0,
    IO_GETKEY_WAITMODE_WAIT
};


uint io_getkey(uint waitMode);

void io_vga_putc_attr(uint x, uint y, char c, uint8_t attr);
void io_vga_clear();
void io_vga_getcursorpos(uint *x, uint *y);
void io_vga_setcursorpos(uint x, uint y);
void io_vga_showcursor(bool show);

// Put char serial
void io_serial_putc(char c);

// Get time
void io_getdatetime(time_t *time);
uint io_gettimer();

// Return NO_ERROR on success
#define DISK_SECTOR_SIZE 512 // hardware sector size in bytes
void io_disks_init_info();
uint io_disk_read(uint disk, uint sector, uint offset, size_t size, void *buff);
uint io_disk_write(uint disk, uint sector, uint offset, size_t size, const void *buff);

// Init lapic, including timer
void lapic_init();
void lapic_eoi(); // Acknowledge
void set_network_IRQ(uint irq); // Set IRQ for network driver
void set_sound_IRQ(uint irq); // Set IRQ for sound driver

// Shutdown computer
void apm_shutdown();

// Enable/disable interrupts
void enable_interrupts();
void disable_interrupts();


// Defines some VGA Text modes

void io_vga_put_c(char c,uint8_t attr);


#endif // _HEISEN_HWIO_KERNEL_INCLUDE_H