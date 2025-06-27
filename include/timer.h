#ifndef __NOVANIX_TIME_H
#define __NOVANIX_TIME_H


#include <common/init.hpp>

#define CMOS_ADDRESS 0x70
#define CMOS_DATA    0x71

// CMOS register indices for RTC
#define RTC_SEC     0x00
#define RTC_MIN     0x02
#define RTC_HOUR    0x04
#define RTC_STATUS_B 0x0B



// Convert BCD to binary if needed
uint8_t bcd_to_bin(uint8_t bcd) {
    return ((bcd / 16) * 10) + (bcd & 0x0F);
}

// Read a byte from CMOS
uint8_t read_cmos(uint8_t reg) {
    outb(CMOS_ADDRESS, reg);
    return inb(CMOS_DATA);
}

/**
 * @brief A function that gets time
 */
void get_time(uint8_t* hour, uint8_t* min, uint8_t* sec) {
    uint8_t h, m, s, status_b;

    s = read_cmos(RTC_SEC);
    m = read_cmos(RTC_MIN);
    h = read_cmos(RTC_HOUR);
    status_b = read_cmos(RTC_STATUS_B);

    // Convert BCD to binary if necessary
    if (!(status_b & 0x04)) {
        s = bcd_to_bin(s);
        m = bcd_to_bin(m);
        h = bcd_to_bin(h);
    }

    *hour = h;
    *min = m;
    *sec = s;
}

VOID __always_inline display_clock() {
    uint8_t h, m, s;
    get_time(&h, &m, &s);
    Novanix::system::printk(Novanix::system::VGA_COLOR_WHITE,stringify(h),0);
    Novanix::system::printk(Novanix::system::VGA_COLOR_WHITE,":",0);
    Novanix::system::printk(Novanix::system::VGA_COLOR_WHITE,stringify(m),0);
    Novanix::system::printk(Novanix::system::VGA_COLOR_WHITE,":",0);
    Novanix::system::printk(Novanix::system::VGA_COLOR_WHITE,stringify(s),0);
    Novanix::system::printk(Novanix::system::VGA_COLOR_WHITE,"\n",0);

}


#endif // __NOVANIX_TIME_H