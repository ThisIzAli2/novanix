/**
 * @author Ali Mirmohammad
 * @file register.h
 * *************************************IMPORTANT ALINIX LICENSE TERM********************************************
 ** This file is part of AliNix.

**AliNix is free software: you can redistribute it and/or modify
**it under the terms of the GNU Affero General Public License as published by
**the Free Software Foundation, either version 3 of the License, or
**(at your option) any later version.

**AliNix is distributed in the hope that it will be useful,
**but WITHOUT ANY WARRANTY; without even the implied warranty of
**MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
**GNU Affero General Public License for more details.

**You should have received a copy of the GNU Affero General Public License
**along with AliNix. If not, see <https://www.gnu.org/licenses/>.
*/

/**
 * @abstraction:
 *  - alinix kernel registers implemented in this header file.
*/
#ifndef __ALINIX__REGISTER_H
#define __ALINIX__REGISTER_H

#include <alinix/types.h>

struct CPUState
{
struct //sGS
{
uint16_t GS;
uint16_t hGS;
};
struct //sFS
{
uint16_t FS;
uint16_t hFS;
};
struct //sES
{
uint16_t ES;
uint16_t hES;
};
struct //sDS
{
uint16_t DS;
uint16_t hDS;
};
union //sEDI
{
uint32_t EDI;
uint16_t DI;
};
union //sESI
{
uint32_t ESI;
uint16_t SI;
};
union //sEBP
{
uint32_t EBP;
uint16_t BP;
};
union //sESP
{
uint32_t ESP;
uint16_t SP;
};
union //sEBX
{
uint32_t EBX;
uint16_t BX;
struct
{
    uint8_t BL;
    uint8_t BH;
};
};
union //sEDX
{
uint32_t EDX;
uint16_t DX;
struct
{
    uint8_t DL;
    uint8_t DH;
};
};
union //sECX
{
uint32_t ECX;
uint16_t CX;
struct
{
    uint8_t CL;
    uint8_t CH;
};
};
union //sEAX
{
uint32_t EAX;
uint16_t AX;
struct
{
    uint8_t AL;
    uint8_t AH;
};
};
uint32_t InterruptNumber;
uint32_t ErrorCode;

union //sEIP
{
uint32_t EIP;
uint16_t IP;
};
struct //sCS
{
uint16_t CS;
uint16_t hCS;
};
union //sEFLAGS
{
uint32_t EFLAGS;
uint16_t FLAGS;
};
union //sUserESP
{
uint32_t UserESP;
uint16_t UserSP;
};
union //sUserSS
{
uint16_t UserSS;
uint16_t hUserSS;
};
} __attribute__((packed));


/* CS_FAULT_EXCEPTION_TYPE values */
#define CS_FAULT_EXCEPTION_TYPE_KABOOM 0x05
#define CS_FAULT_EXCEPTION_TYPE_CS_RESOURCE_TERMINATED 0x0F
#define CS_FAULT_EXCEPTION_TYPE_CS_BUS_FAULT 0x48
#define CS_FAULT_EXCEPTION_TYPE_CS_INHERIT_FAULT 0x4B
#define CS_FAULT_EXCEPTION_TYPE_INSTR_INVALID_PC 0x50
#define CS_FAULT_EXCEPTION_TYPE_INSTR_INVALID_ENC 0x51
#define CS_FAULT_EXCEPTION_TYPE_INSTR_BARRIER_FAULT 0x55
#define CS_FAULT_EXCEPTION_TYPE_DATA_INVALID_FAULT 0x58
#define CS_FAULT_EXCEPTION_TYPE_TILE_RANGE_FAULT 0x59
#define CS_FAULT_EXCEPTION_TYPE_ADDR_RANGE_FAULT 0x5A
#define CS_FAULT_EXCEPTION_TYPE_IMPRECISE_FAULT 0x5B
#define CS_FAULT_EXCEPTION_TYPE_RESOURCE_EVICTION_TIMEOUT 0x69
#define CS_FAULT_EXCEPTION_TYPE_TRANSLATION_FAULT_L0 0xC0
#define CS_FAULT_EXCEPTION_TYPE_TRANSLATION_FAULT_L1 0xC1
#define CS_FAULT_EXCEPTION_TYPE_TRANSLATION_FAULT_L2 0xC2
#define CS_FAULT_EXCEPTION_TYPE_TRANSLATION_FAULT_L3 0xC3
#define CS_FAULT_EXCEPTION_TYPE_TRANSLATION_FAULT_L4 0xC4
#define CS_FAULT_EXCEPTION_TYPE_PERMISSION_FAULT_0 0xC8
#define CS_FAULT_EXCEPTION_TYPE_PERMISSION_FAULT_1 0xC9
#define CS_FAULT_EXCEPTION_TYPE_PERMISSION_FAULT_2 0xCA
#define CS_FAULT_EXCEPTION_TYPE_PERMISSION_FAULT_3 0xCB
#define CS_FAULT_EXCEPTION_TYPE_ACCESS_FLAG_1 0xD9
#define CS_FAULT_EXCEPTION_TYPE_ACCESS_FLAG_2 0xDA
#define CS_FAULT_EXCEPTION_TYPE_ACCESS_FLAG_3 0xDB
#define CS_FAULT_EXCEPTION_TYPE_ADDRESS_SIZE_FAULT_IN 0xE0
#define CS_FAULT_EXCEPTION_TYPE_ADDRESS_SIZE_FAULT_OUT_0 0xE4
#define CS_FAULT_EXCEPTION_TYPE_ADDRESS_SIZE_FAULT_OUT_1 0xE5
#define CS_FAULT_EXCEPTION_TYPE_ADDRESS_SIZE_FAULT_OUT_2 0xE6
#define CS_FAULT_EXCEPTION_TYPE_ADDRESS_SIZE_FAULT_OUT_3 0xE7
#define CS_FAULT_EXCEPTION_TYPE_MEMORY_ATTRIBUTE_FAULT_0 0xE8
#define CS_FAULT_EXCEPTION_TYPE_MEMORY_ATTRIBUTE_FAULT_1 0xE9
#define CS_FAULT_EXCEPTION_TYPE_MEMORY_ATTRIBUTE_FAULT_2 0xEA
#define CS_FAULT_EXCEPTION_TYPE_MEMORY_ATTRIBUTE_FAULT_3 0xEB


#define CS_FATAL_EXCEPTION_TYPE_CS_CONFIG_FAULT 0x40
#define CS_FATAL_EXCEPTION_TYPE_CS_UNRECOVERABLE 0x41
#define CS_FATAL_EXCEPTION_TYPE_CS_ENDPOINT_FAULT 0x44
#define CS_FATAL_EXCEPTION_TYPE_CS_BUS_FAULT 0x48
#define CS_FATAL_EXCEPTION_TYPE_CS_INVALID_INSTRUCTION 0x49
#define CS_FATAL_EXCEPTION_TYPE_CS_CALL_STACK_OVERFLOW 0x4A
#define CS_FATAL_EXCEPTION_TYPE_FIRMWARE_INTERNAL_ERROR 0x68

#define GPU_FAULTSTATUS_EXCEPTION_TYPE_OK 0x00
#define GPU_FAULTSTATUS_EXCEPTION_TYPE_GPU_BUS_FAULT 0x80
#define GPU_FAULTSTATUS_EXCEPTION_TYPE_GPU_SHAREABILITY_FAULT 0x88
#define GPU_FAULTSTATUS_EXCEPTION_TYPE_SYSTEM_SHAREABILITY_FAULT 0x89
#define GPU_FAULTSTATUS_EXCEPTION_TYPE_GPU_CACHEABILITY_FAULT 0x8A


#endif /*__ALINIX__REGISTER_H*/