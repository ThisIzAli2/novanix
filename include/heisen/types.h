// /* SPDX-License-Identifier: GPL-2.0 */
// #ifndef _LINUX_TYPES_H
// #define _LINUX_TYPES_H

// #define __EXPORTED_HEADERS__
// #include <uapi/heisen/types.h>
// #include <heisen/typing.h>
// #define NULL 0

// typedef unsigned char uint8;
// typedef unsigned short uint16;
// typedef unsigned int uint32;
// typedef signed char sint8;
// typedef signed short sint16;
// typedef signed int sint32;
// typedef uint8 byte;
// typedef uint16 word;
// typedef uint32 dword;
// typedef unsigned long long uint64;
// typedef long long int64;
// typedef int64 qword;
// typedef uint32 size_t; 
// typedef uint32 fd_t;
// typedef enum {
//     FALSE,
//     TRUE
// } BOOL;
// #define NULL 0

// typedef unsigned char uint8_t;
// typedef unsigned short uint16_t;
// typedef unsigned int uint32_t;
// typedef unsigned long long uint64_t;

// typedef signed char int8_t;
// typedef signed short int16_t;
// typedef signed int int32_t;
// typedef signed long long int64_t;

// typedef unsigned int size_t;

// typedef int pid_t;

// typedef struct regs16 {
//     uint16_t di;
//     uint16_t si;
//     uint16_t bp;
//     uint16_t sp;
//     uint16_t bx;
//     uint16_t dx;
//     uint16_t cx;
//     uint16_t ax;
//     uint16_t gs;
//     uint16_t fs;
//     uint16_t es;
//     uint16_t ds;
//     uint16_t eflags;
// } __attribute__ ((packed)) regs16_t;

// typedef __builtin_va_list va_list;
// #define va_start(ap,last) __builtin_va_start(ap, last)
// #define va_end(ap) __builtin_va_end(ap)
// #define va_arg(ap,type) __builtin_va_arg(ap,type)

// #ifndef __ASSEMBLY__

// #define DECLARE_BITMAP(name,bits) \
// 	unsigned long name[BITS_TO_LONGS(bits)]

// #ifdef __SIZEOF_INT128__
// typedef __s128 s128;
// typedef __u128 u128;
// #endif

// typedef uint32_t __kernel_dev_t;

// typedef __kernel_fd_set		fd_set;
// typedef __kernel_dev_t		dev_t;
// typedef __kernel_ulong_t	ino_t;
// typedef __kernel_mode_t		mode_t;
// typedef unsigned short		umode_t;
// typedef uint32_t			nlink_t;
// typedef __kernel_off_t		off_t;
// typedef __kernel_pid_t		pid_t;
// typedef __kernel_daddr_t	daddr_t;
// typedef __kernel_key_t		key_t;
// typedef __kernel_suseconds_t	suseconds_t;
// typedef __kernel_timer_t	timer_t;
// typedef __kernel_clockid_t	clockid_t;
// typedef __kernel_mqd_t		mqd_t;

// typedef _Bool			bool;

// typedef __kernel_uid32_t	uid_t;
// typedef __kernel_gid32_t	gid_t;
// typedef __kernel_uid16_t        uid16_t;
// typedef __kernel_gid16_t        gid16_t;

// typedef unsigned long		uintptr_t;
// typedef long			intptr_t;

// #ifdef CONFIG_HAVE_UID16
// /* This is defined by include/asm-{arch}/posix_types.h */
// typedef __kernel_old_uid_t	old_uid_t;
// typedef __kernel_old_gid_t	old_gid_t;
// #endif /* CONFIG_UID16 */

// #if defined(__GNUC__)
// typedef __kernel_loff_t		loff_t;
// #endif

// /*
//  * The following typedefs are also protected by individual ifdefs for
//  * historical reasons:
//  */
// #ifndef _SIZE_T
// #define _SIZE_T
// typedef __kernel_size_t		size_t;
// #endif

// #ifndef _SSIZE_T
// #define _SSIZE_T
// typedef __kernel_ssize_t	ssize_t;
// #endif

// #ifndef _PTRDIFF_T
// #define _PTRDIFF_T
// typedef __kernel_ptrdiff_t	ptrdiff_t;
// #endif

// #ifndef _CLOCK_T
// #define _CLOCK_T
// typedef __kernel_clock_t	clock_t;
// #endif

// #ifndef _CADDR_T
// #define _CADDR_T
// typedef __kernel_caddr_t	caddr_t;
// #endif

// /* bsd */
// typedef unsigned char		u_char;
// typedef unsigned short		u_short;
// typedef unsigned int		u_int;
// typedef unsigned long		u_long;

// /* sysv */
// typedef unsigned char		unchar;
// typedef unsigned short		ushort;
// typedef unsigned int		uint;
// typedef unsigned long		ulong;

// #ifndef __BIT_TYPES_DEFINED__
// #define __BIT_TYPES_DEFINED__

// typedef uint8_t			u_int8_t;
// typedef s8			int8_t;
// typedef uint16_t			u_int16_t;
// typedef s16			int16_t;
// typedef uint32_t			u_int32_t;
// typedef s32			int32_t;

// #endif /* !(__BIT_TYPES_DEFINED__) */

// typedef uint8_t			uint8_t;
// typedef uint16_t			uint16_t;
// typedef uint32_t			uint32_t;

// #if defined(__GNUC__)
// typedef uint64_t			uint64_t;
// typedef uint64_t			u_int64_t;
// typedef s64			int64_t;
// #endif

// /* this is a special 64bit data type that is 8-byte aligned */
// #define aligned_u64		__aligned_u64
// #define aligned_be64		__aligned_be64
// #define aligned_le64		__aligned_le64

// /* Nanosecond scalar representation for kernel time values */
// typedef s64	ktime_t;

// /**
//  * The type used for indexing onto a disc or disc partition.
//  *
//  * Linux always considers sectors to be 512 bytes long independently
//  * of the devices real block size.
//  *
//  * blkcnt_t is the type of the inode's block count.
//  */
// typedef uint64_t sector_t;
// typedef uint64_t blkcnt_t;

// /*
//  * The type of an index into the pagecache.
//  */
// #define pgoff_t unsigned long

// /*
//  * A dma_addr_t can hold any valid DMA address, i.e., any address returned
//  * by the DMA API.
//  *
//  * If the DMA API only uses 32-bit addresses, dma_addr_t need only be 32
//  * bits wide.  Bus addresses, e.g., PCI BARs, may be wider than 32 bits,
//  * but drivers do memory-mapped I/O to ioremapped kernel virtual addresses,
//  * so they don't care about the size of the actual bus addresses.
//  */
// #ifdef CONFIG_ARCH_DMA_ADDR_T_64BIT
// typedef uint64_t dma_addr_t;
// #else
// typedef uint32_t dma_addr_t;
// #endif

// typedef unsigned int __bitwise gfp_t;
// typedef unsigned int __bitwise slab_flags_t;
// typedef unsigned int __bitwise fmode_t;

// #ifdef CONFIG_PHYS_ADDR_T_64BIT
// typedef uint64_t phys_addr_t;
// #else
// typedef uint32_t phys_addr_t;
// #endif

// typedef phys_addr_t resource_size_t;

// /*
//  * This type is the placeholder for a hardware interrupt number. It has to be
//  * big enough to enclose whatever representation is used by a given platform.
//  */
// typedef unsigned long irq_hw_number_t;

// typedef struct {
// 	int counter;
// } atomic_t;

// #define ATOMIC_INIT(i) { (i) }

// #ifdef CONFIG_64BIT
// typedef struct {
// 	s64 counter;
// } atomic64_t;
// #endif

// typedef struct {
// 	atomic_t refcnt;
// } rcuref_t;

// #define RCUREF_INIT(i)	{ .refcnt = ATOMIC_INIT(i - 1) }

// struct list_head {
// 	struct list_head *next, *prev;
// };

// struct hlist_head {
// 	struct hlist_node *first;
// };

// struct hlist_node {
// 	struct hlist_node *next, **pprev;
// };

// struct ustat {
// 	__kernel_daddr_t	f_tfree;
// #ifdef CONFIG_ARCH_32BIT_USTAT_F_TINODE
// 	unsigned int		f_tinode;
// #else
// 	unsigned long		f_tinode;
// #endif
// 	char			f_fname[6];
// 	char			f_fpack[6];
// };

// /**
//  * struct callback_head - callback structure for use with RCU and task_work
//  * @next: next update requests in a list
//  * @func: actual update function to call after the grace period.
//  *
//  * The struct is aligned to size of pointer. On most architectures it happens
//  * naturally due ABI requirements, but some architectures (like CRIS) have
//  * weird ABI and we need to ask it explicitly.
//  *
//  * The alignment is required to guarantee that bit 0 of @next will be
//  * clear under normal conditions -- as long as we use call_rcu() or
//  * call_srcu() to queue the callback.
//  *
//  * This guarantee is important for few reasons:
//  *  - future call_rcu_lazy() will make use of lower bits in the pointer;
//  *  - the structure shares storage space in struct page with @compound_head,
//  *    which encode PageTail() in bit 0. The guarantee is needed to avoid
//  *    false-positive PageTail().
//  */
// struct callback_head {
// 	struct callback_head *next;
// 	void (*func)(struct callback_head *head);
// } __attribute__((aligned(sizeof(void *))));
// #define rcu_head callback_head

// typedef void (*rcu_callback_t)(struct rcu_head *head);
// typedef void (*call_rcu_func_t)(struct rcu_head *head, rcu_callback_t func);

// typedef void (*swap_r_func_t)(void *a, void *b, int size, const void *priv);
// typedef void (*swap_func_t)(void *a, void *b, int size);

// typedef int (*cmp_r_func_t)(const void *a, const void *b, const void *priv);
// typedef int (*cmp_func_t)(const void *a, const void *b);

// #endif /*  __ASSEMBLY__ */
// #endif /* _LINUX_TYPES_H */