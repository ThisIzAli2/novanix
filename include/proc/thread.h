#ifndef THREAD_H
#define THREAD_H

#include <types.h>

typedef struct thread {
    pid_t pid;                      // thread id
    int time;                       // thread's time slice in ms
    int main;                       // if it's the main thread
    int state;                      // thread's state
    void *parent;                   // pointer to proc
    uint32_t eip;                   // start instruction pointer
    uint32_t esp;                   // start thread's stack pointer
    uint32_t stack_limit;           // thread's stack limit pointer
    uint32_t esp_kernel;            // thread's kernel stack pointer
    uint32_t stack_kernel_limit;    // thread's kernel stack limit
    uint32_t heap;                  // thread's heap pointer
    uint32_t heap_limit;            // thread's heap limit pointer
    uint32_t image_base;
    uint32_t image_size;
    struct thread *next;
    struct thread *prec;
} thread_t;

thread_t *create_thread();
int start_thread();
void stop_thread(int code);

#endif