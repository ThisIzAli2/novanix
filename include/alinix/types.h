/**
 * @author Ali Mirmohammad
 * @file types.h
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
 *  - Defines kernel needed data types.
 *  - Defines necessary macros. 
*/
#ifndef __ALINIX_KERNEL__TYPES_H_HEADER_
#define __ALINIX_KERNEL__TYPES_H_HEADER_

#include <alinix/_types.h>
#include <alinix/enums.h>



#define ATOMIC_INIT(i) { (i) }
///////////////////////////////////////////////////////////////////
typedef int pid_t;
typedef unsigned long irq_hw_number_t;
typedef unsigned int  gfp_t;
typedef char                        int8_t;
typedef unsigned char               uint8_t;
typedef short                       int16_t;
typedef unsigned short              uint16_t;
typedef int                         int32_t;
typedef unsigned int                uint32_t;
typedef long long int               int64_t;
typedef unsigned long long int      uint64_t;
typedef unsigned long long          uintptr_t;
typedef signed char               sint8_t;
typedef signed short              sint16_t;
typedef signed int               sint32_t;
typedef signed long long int      sint64_t;
typedef unsigned int            paddr_t;
typedef int udi_channel_t; // TODO: Fix here(change the defined type)
typedef int udi_origin_t; //TODO: Fix here('''')
typedef uint8_t byte;
typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;
typedef char *va_list;
typedef uint32_t phys_addr_t;
typedef long long loff_t;
typedef phys_addr_t resource_size_t;
typedef sint64_t ktime_t;
typedef	unsigned int	uint;		/* Sys V compatibility */
typedef unsigned char byte_t; // For  backward compatibility
typedef uint8_t udi_ubit8_t;
//! This might run into problem (size_t)
typedef unsigned long int size_t;
typedef size_t ssize_t;
///////////////////////////////////////////////////////////////////
#if !defined(__cplusplus)
//TODO Fix here
typedef enum  {false = 0, true = 1} bool;
// #include <stdbool.h>
//?++<<<include <stdbool.h>
#endif /*__cplusplus*/

/////////////////////////
// Defining the extra system types
typedef uint16_t __le16;

#ifndef NULL
#define NULL (void *)0
#endif /*NULL*/

#define CONSOLE_BUFFER_LENGTH 64
////////////////////
/**
 * @brief Networking types
*/
typedef struct ip_addr ip_addr_t;
typedef struct ip_addr_packed ip_addr_p_t;

int strlen(const char* str);
// bool strcmp(const char* strA, const char* strB);
// bool strncmp(const char* s1, const char* s2, int n);
int IndexOf(const char* str, char c, uint32_t skip);
bool Contains(const char* str, char c);

#if !defined(ALINIX_NULL_CPP_NULL_PTR) && defined(__cplusplus) && !defined(NULL)
#define  ALINIX_NULL_CPP_NULL ALINIX_NULL_CPP_NULL_PTR

#endif /*ALINIX_NULL_CPP_NULL_PTR*/


////////////////////////////////////////
typedef struct 
{
    uint32_t signature;     // USBC in hexadecimal, acting as magic number
    uint32_t tag;           // Signature
    uint32_t transferLen;   // Number of bytes to transfer excluding size of CBW
    uint8_t flags;          // 7: 0=Out 1=In, 6:0=Reserved
    uint8_t lun;            // 7:4 Reserved, 3:0 Logical Unit Number
    uint8_t cmdLen;         // Length of command in next field [1-16]
    uint8_t command[16];    // Command Data
} __attribute__((packed)) CommandBlockWrapper;


typedef struct {
    void* controller; // Which controller is controlling this disk device
    uint32_t controllerIndex; // The real number for the disk on the controller
    char* identifier; // Disk Identifier
    DiskType type; // Type of disk
    uint64_t size; // Size of disk in bytes
    uint32_t numBlocks; // Number of data blocks
    uint32_t blockSize; // Size of one block of data
} Disk;

typedef struct {
  uint64_t val;
}kernel_cap_t;


// Define data types for as macros here
#define RET return
#define POSITIVE unsigned int
#define NEGATIVE signed int
#define NUMBER int 
#ifndef __cplusplus

#define STRING char*

#endif // __cplusplus
#define REAL  double
#define VOID void
#define EXTERNAL extern
#define PRIVATE static
#define CONSTANT const
#define NO_ARGS void
#define NO_RETURN VOID
#define __always_inline inline
#define __ksym __attribute__((section(".ksyms")))
#define RET return


/////////////////////
struct callback_head {
	struct callback_head *next;
	void (*func)(struct callback_head *head);
} __attribute__((aligned(sizeof(void *))));
#define rcu_head callback_head


typedef enum {
#define LWIP_MEMPOOL(name,num,size,desc)  MEMP_##name,
  MEMP_MAX
} memp_t;

typedef struct {
	int counter;
} atomic_t;

typedef struct {
    void *data;         // Pointer to the buffer's data
    size_t length;      // Length of the data in the buffer
    size_t capacity;    // Total capacity of the buffer
} udi_buf_t;


struct hlist_node {
	struct hlist_node *next, **pprev;
};

struct hlist_head {
	struct hlist_node *first;
};


typedef struct raw_spinlock {
	unsigned int magic, owner_cpu;
	void *owner;
} raw_spinlock_t;

typedef struct pm_message {
	int event;
} pm_message_t;



typedef struct regs16 {
    uint16_t di;
    uint16_t si;
    uint16_t bp;
    uint16_t sp;
    uint16_t bx;
    uint16_t dx;
    uint16_t cx;
    uint16_t ax;
    uint16_t gs;
    uint16_t fs;
    uint16_t es;
    uint16_t ds;
    uint16_t eflags;
} __attribute__ ((packed)) regs16_t;

/* The core IPC message type used by UDI. Every IPC message contains
 * this base type, and new message types can be created by extending
 * this type. Every UDI IPC message (aka "control block") is based
 * on this type, the udi_cb_t structure.
 */
typedef struct {
	udi_channel_t channel;
	void *context;
	void *scratch;
	void *initiator_context;
	udi_origin_t origin;
} udi_cb_t;

typedef __builtin_va_list va_list;
#define va_start(ap,last) __builtin_va_start(ap, last)
#define va_end(ap) __builtin_va_end(ap)
#define va_arg(ap,type) __builtin_va_arg(ap,type)

#endif /*__ALINIX_KERNEL__TYPES_H_HEADER_*/