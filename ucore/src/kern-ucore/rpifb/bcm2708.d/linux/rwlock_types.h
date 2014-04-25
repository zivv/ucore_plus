#ifndef __LINUX_RWLOCK_TYPES_H__
#define __LINUX_RWLOCK_TYPES_H__

typedef struct {
	arch_rwlock_t raw_lock;
#ifdef CONFIG_GENERIC_LOCKBREAK
	unsigned int break_lock;
#endif
#ifdef CONFIG_DEBUG_SPINLOCK
	unsigned int magic, owner_cpu;
	void *owner;
#endif
#ifdef CONFIG_DEBUG_LOCK_ALLOC
	struct lockdep_map dep_map;
#endif
} rwlock_t;

#endif /* ! __LINUX_RWLOCK_TYPES_H__ */
