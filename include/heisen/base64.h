#ifndef _HEISEN_BASE64_H
#define _HEISEN_BASE64_H

#include <heisen/typing.h>

#define BASE64_CHARS(nbytes)   DIV_ROUND_UP((nbytes) * 4, 3)

int base64_encode(const uint8_t *src, int len, char *dst);
int base64_decode(const char *src, int len, uint8_t *dst);

#endif /* _HEISEN_BASE64_H */