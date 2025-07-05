#ifndef ___NOVANIX_PORTS_H
#define ___NOVANIX_PORTS_H


#include <common/types.h>

using namespace Novanix::common;

// inline void outb(uint16_t port, uint8_t data) {
//     asm volatile ("outb %0, %1" : : "a"(data), "dN"(port));
// }

// inline uint8_t inb(uint16_t port) {
//     uint8_t result;
//     asm volatile ("inb %1, %0" : "=a"(result) : "dN"(port));
//     return result;
// }

#endif