#ifndef __FORMATING_H_NOVA
#define __FORMATING_H_NOVA

#include <common/types.h>
#include <statements.h>


DECLARE_NAME_SPACE

uint8_t binary_to_bcd(uint8_t bin) {
    return ((bin / 10) << 4) | (bin % 10);
}



#endif // __FORMATING_H_NOVA