#ifndef PROC_H
#define PROC_H

#include <hal/tss.h>
#include <mm/memory.h>
#include <types.h>
#include <proc/thread.h>

#define PROC_NULL       -1

#define PROC_STOPPED    0
#define PROC_ACTIVE     1
#define PROC_NEW        2

#define RETURN_ADDR 0x400000

struct regs {
    uint32_t ds;
    uint32_t es;
    uint32_t fs;
    uint32_t gs;
    uint32_t edi;
    uint32_t esi;
    uint32_t ebp;
    uint32_t esp;
    uint32_t ebx;
    uint32_t edx;
    uint32_t ecx;
    uint32_t eax;
    uint32_t eip;
    uint32_t cs;
};

struct regs_error {
    uint32_t ds;
    uint32_t es;
    uint32_t fs;
    uint32_t gs;
    uint32_t edi;
    uint32_t esi;
    uint32_t ebp;
    uint32_t esp;
    uint32_t ebx;
    uint32_t edx;
    uint32_t ecx;
    uint32_t eax;
    uint32_t error;
    uint32_t eip;
    uint32_t cs;
};

typedef struct proc {
    char name[16];
    int state;
    page_dir_t *pdir;
    int threads;
    thread_t *thread_list;
    struct proc *next;
    struct proc *prec;
} process_t;

extern void end_process();

int start_proc(char *name, char *arguments);
int build_stack(thread_t *thread, page_dir_t *pdir, int nthreads);
int heap_fill(thread_t *thread, char *name, char *arguments, uint32_t *argc, uint32_t *argv1);
int stack_fill(thread_t *thread, uint32_t argc, uint32_t argv);
int build_heap(thread_t *thread, page_dir_t *pdir, int nthreads);
void end_proc(int ret);
void remove_proc(int pid);
int start_kernel_proc(char *name, void *addr);
int proc_state(int id);