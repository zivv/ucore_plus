#ifndef __LINUX_SPINLOCK_TYPES_UP_H__
#define __LINUX_SPINLOCK_TYPES_UP_H__

typedef struct { } arch_spinlock_t;

#define __ARCH_SPIN_LOCK_UNLOCKED { }

typedef struct {
	/* no debug version on UP */
} arch_rwlock_t;

#endif /* ! __LINUX_SPINLOCK_TYPES_UP_H__ */
