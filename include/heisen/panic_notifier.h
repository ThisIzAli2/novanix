#ifndef _HEISEN_PANIC_NOTIFIERS_H
#define _HEISEN_PANIC_NOTIFIERS_H

#include <heisen/notifier.h>
#include <heisen/types.h>

extern struct atomic_notifier_head panic_notifier_list;

extern bool crash_kexec_post_notifiers;

#endif	/* _HEISEN_PANIC_NOTIFIERS_H */