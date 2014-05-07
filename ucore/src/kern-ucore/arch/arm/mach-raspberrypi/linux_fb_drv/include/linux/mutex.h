#ifndef __LINUX_MUTEX_H__
#define __LINUX_MUTEX_H__

#include <linux/list.h>
#include <linux/spinlock_types.h>
#include <linux/linkage.h>
#include <linux/lockdep.h>

#include <linux/atomic.h>

struct mutex {
	/* 1: unlocked, 0: locked, negative: locked, possible waiters */
	atomic_t		count;
	spinlock_t		wait_lock;
	struct list_head	wait_list;
#if defined(CONFIG_DEBUG_MUTEXES) || defined(CONFIG_SMP)
	struct task_struct	*owner;
#endif
#ifdef CONFIG_MUTEX_SPIN_ON_OWNER
	void			*spin_mlock;	/* Spinner MCS lock */
#endif
#ifdef CONFIG_DEBUG_MUTEXES
	const char 		*name;
	void			*magic;
#endif
#ifdef CONFIG_DEBUG_LOCK_ALLOC
	struct lockdep_map	dep_map;
#endif
};

extern void mutex_lock(struct mutex *lock);

extern int mutex_trylock(struct mutex *lock);
extern void mutex_unlock(struct mutex *lock);

#endif /* ! __LINUX_MUTEX_H__ */
