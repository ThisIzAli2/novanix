#ifndef _HEISEN_SEM_H
#define _HEISEN_SEM_H

#include <uapi/heisen/sem.h>
#include <heisen/sem_types.h>

struct task_struct;

#ifdef CONFIG_SYSVIPC

extern int copy_semundo(unsigned long clone_flags, struct task_struct *tsk);
extern void exit_sem(struct task_struct *tsk);

#else

static inline int copy_semundo(unsigned long clone_flags, struct task_struct *tsk)
{
	return 0;
}

static inline void exit_sem(struct task_struct *tsk)
{
	return;
}
#endif

#endif /* _HEISEN_SEM_H */