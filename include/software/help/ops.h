#ifndef __NOVANIX_KERNEL_OPS_H
#define __NOVANIX_KERNEL_OPS_H


#include <common/init.hpp>

char binary_to_char(const char* bin);
void binary_to_string(const char* binary_input, char* output);
uint32_t string_to_binary(const char* input);
void char_to_binary(uint8_t c, char* buffer);
uint32_t strlen_kernel(const char* str);

char inline binary_to_char(const char* bin) {
    char result = 0;
    for (int i = 0; i < 8; ++i) {
        result <<= 1;
        if (bin[i] == '1') {
            result |= 1;
        }
    }
    return result;
}

#endif /*__NOVANIX_KERNEL_OPS_H*/