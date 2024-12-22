#ifndef _HEISEN_RESOURCE_H
#define _HEISEN_RESOURCE_H

#include <uapi/heisen/resource.h>


struct task_struct;

void getrusage(struct task_struct *p, int who, struct rusage *ru);

#endif