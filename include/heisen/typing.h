#ifndef TYPING_H
#define  TYPING_H
#define NULL 0

#ifndef __TEST__
#include <sys/types.h>
#endif

#define TLS __attribute__((address_space(256)))



#define PRIVATE __attribute__((visibility("hidden")))
#define VOID void
#define INTEGER int
#define STRING char*
#define FLOAT  double


typedef unsigned char uint8;
typedef unsigned short uint16;
typedef unsigned int uint32;
typedef signed char sint8;
typedef signed short sint16;
typedef signed int sint32;
typedef uint8 byte;
typedef uint16 word;
typedef uint32 dword;
typedef unsigned long long uint64;
typedef long long int64;
typedef int64 qword;
typedef uint32 size_t; 
typedef uint32 fd_t;
typedef enum {
    FALSE,
    TRUE
} BOOL;
#define NULL 0

typedef long		__kernel_long_t;
typedef unsigned long	__kernel_ulong_t;

#ifndef __kernel_ino_t
typedef __kernel_ulong_t __kernel_ino_t;
#endif

#ifndef __kernel_mode_t
typedef unsigned int	__kernel_mode_t;
#endif

#ifndef __kernel_pid_t
typedef int		__kernel_pid_t;
#endif

#ifndef __kernel_ipc_pid_t
typedef int		__kernel_ipc_pid_t;
#endif

#ifndef __kernel_uid_t
typedef unsigned int	__kernel_uid_t;
typedef unsigned int	__kernel_gid_t;
#endif

#ifndef __kernel_suseconds_t
typedef __kernel_long_t		__kernel_suseconds_t;
#endif

#ifndef __kernel_daddr_t
typedef int		__kernel_daddr_t;
#endif

typedef enum {
  timer_features_none = 0,
  timer_features_oneshot = (1 << 0),
  timer_features_periodic = (1 << 1),
  timer_features_read = (1 << 2),
  timer_features_persistent = (1 << 3),
  timer_features_absolute = (1 << 4),
  timer_features_64bit = (1 << 5),
  timer_features_write = (1 << 6),
  timer_features_local = (1 << 7),
  timer_features_pcie_msg_intr = (1 << 8),
  timer_features_fixed_intr = (1 << 9),
  timer_features_counter = (1 << 10),
} timer_features_t;

typedef struct timer_handlers timer_handlers_t;

#ifndef __kernel_uid32_t
typedef unsigned int	__kernel_uid32_t;
typedef unsigned int	__kernel_gid32_t;
#endif

#ifndef __kernel_old_uid_t
typedef __kernel_uid_t	__kernel_old_uid_t;
typedef __kernel_gid_t	__kernel_old_gid_t;
#endif

#ifndef __kernel_old_dev_t
typedef unsigned int	__kernel_old_dev_t;
#endif

/*
 * Most 32 bit architectures use "unsigned int" size_t,
 * and all 64 bit architectures use "unsigned long" size_t.
 */
#ifndef __kernel_size_t
#if __BITS_PER_LONG != 64
typedef unsigned int	__kernel_size_t;
typedef int		__kernel_ssize_t;
typedef int		__kernel_ptrdiff_t;
#else
typedef __kernel_ulong_t __kernel_size_t;
typedef __kernel_long_t	__kernel_ssize_t;
typedef __kernel_long_t	__kernel_ptrdiff_t;
#endif
#endif

#ifndef __kernel_fsid_t
typedef struct {
	int	val[2];
} __kernel_fsid_t;
#endif

/*
 * anything below here should be completely generic
 */
typedef __kernel_long_t	__kernel_off_t;
typedef long long	__kernel_loff_t;
typedef __kernel_long_t	__kernel_old_time_t;
#ifndef __KERNEL__
typedef __kernel_long_t	__kernel_time_t;
#endif
typedef long long __kernel_time64_t;
typedef __kernel_long_t	__kernel_clock_t;
typedef int		__kernel_timer_t;
typedef int		__kernel_clockid_t;
typedef char *		__kernel_caddr_t;
typedef unsigned short	__kernel_uid16_t;
typedef unsigned short	__kernel_gid16_t;


typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int uint32_t;
typedef unsigned long long uint64_t;

typedef signed char int8_t;
typedef signed short int16_t;
typedef signed int int32_t;
typedef signed long long int64_t;

typedef unsigned long long int size_t;

typedef int pid_t;

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


typedef _Bool bool;  /* for boolean expressions */


#endif // TYPING_H