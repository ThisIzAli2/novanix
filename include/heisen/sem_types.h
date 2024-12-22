#ifndef _HEISEN_SEM_TYPES_H
#define _HEISEN_SEM_TYPES_H

struct sem_undo_list;

struct sysv_sem {
#ifdef CONFIG_SYSVIPC
	struct sem_undo_list *undo_list;
#endif
};

#endif /* _HEISEN_SEM_TYPES_H */