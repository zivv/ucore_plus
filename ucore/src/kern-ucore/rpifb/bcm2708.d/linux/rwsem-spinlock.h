#ifndef __LINUX_RWSEM_SPINLOCK_H__
#define __LINUX_RWSEM_SPINLOCK_H__

struct rw_semaphore {
	__s32			activity;
	raw_spinlock_t		wait_lock;
	struct list_head	wait_list;
#ifdef CONFIG_DEBUG_LOCK_ALLOC
	struct lockdep_map dep_map;
#endif
};

#endif /* ! __LINUX_RWSEM_SPINLOCK_H__ */
