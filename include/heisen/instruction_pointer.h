#ifndef __HEISEN_INSTRUCTION_POINTER_H
#define __HEISEN_INSTRUCTION_POINTER_H


#include <asm/linkage.h>

#define _RET_IP (unsigned long)__builtin_return_address(0)

#ifndef _THIS_IP
#define _THIS_IP_  ({ __label__ __here; __here: (unsigned long)&&__here; })
#endif



#endif // __HEISEN_INSTRUCTION_POINTER_H