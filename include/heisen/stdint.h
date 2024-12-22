#ifndef _STDINT_H_
#define _STDINT_H_

#define S(x) #x
#define S_(x) S(x)
#define S__LINE__ S_(__LINE__)

#define LE_ENDIAN 1
#define GE_ENDIAN 2

typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int uint32_t;
typedef unsigned long int uint64_t;

typedef signed char int8_t;
typedef signed short int16_t;
typedef signed int int32_t;
typedef signed long int int64_t;

typedef long int off_t;
typedef unsigned long int size_t;

typedef long int intptr_t;
typedef unsigned long int uintptr_t;

typedef int bool;

#define true 1
#define false 0

#define CUR_ENDIAN LE_ENDIAN
#define TLS __attribute__((address_space(256)))

#endif