#ifndef _LINUX_CRC7_H
#define _LINUX_CRC7_H
#include <heisen/typing.h>

extern const uint8_t crc7_be_syndrome_table[256];

static inline uint8_t crc7_be_byte(uint8_t crc, uint8_t data)
{
	return crc7_be_syndrome_table[crc ^ data];
}

extern uint8_t crc7_be(uint8_t crc, const uint8_t *buffer, size_t len);

#endif