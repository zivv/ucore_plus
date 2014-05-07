#ifndef __LINUX_RTMUTEX_H__
#define __LINUX_RTMUTEX_H__

#include <linux/linkage.h>
#include <linux/plist.h>
#include <linux/spinlock_types.h>

struct rt_mutex {
	raw_spinlock_t		wait_lock;
	struct plist_head	wait_list;
	struct task_struct	*owner;
#ifdef CONFIG_DEBUG_RT_MUTEXES
	int			save_state;
	const char 		*name, *file;
	int			line;
	void			*magic;
#endif
};

struct rt_mutex_waiter;

#endif /* ! __LINUX_RTMUTEX_H__ */
