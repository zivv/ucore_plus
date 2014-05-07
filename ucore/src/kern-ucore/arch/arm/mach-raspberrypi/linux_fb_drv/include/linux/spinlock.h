#ifndef __LINUX_SPINLOCK_H__
#define __LINUX_SPINLOCK_H__

#define __LINUX_SPINLOCK_H

#include <linux/typecheck.h>
#include <linux/preempt.h>
#include <linux/linkage.h>
#include <linux/compiler.h>
#include <linux/irqflags.h>
#include <linux/thread_info.h>
#include <linux/kernel.h>
#include <linux/stringify.h>
#include <linux/bottom_half.h>
#include <asm/barrier.h>

#include <linux/spinlock_types.h>

# include <linux/spinlock_up.h>

# define raw_spin_lock_init(lock)				\
	do { *(lock) = __RAW_SPIN_LOCK_UNLOCKED(lock); } while (0)

#define raw_spin_is_locked(lock)	arch_spin_is_locked(&(lock)->raw_lock)

#define raw_spin_is_contended(lock)	arch_spin_is_contended(&(lock)->raw_lock)

#define smp_mb__before_spinlock()	smp_wmb()

#define raw_spin_unlock_wait(lock)	arch_spin_unlock_wait(&(lock)->raw_lock)

#define raw_spin_trylock(lock)	__cond_lock(lock, _raw_spin_trylock(lock))

#define raw_spin_lock(lock)	_raw_spin_lock(lock)

#define raw_spin_lock_irqsave(lock, flags)		\
	do {						\
		typecheck(unsigned long, flags);	\
		_raw_spin_lock_irqsave(lock, flags);	\
	} while (0)

#define raw_spin_lock_irq(lock)		_raw_spin_lock_irq(lock)
#define raw_spin_lock_bh(lock)		_raw_spin_lock_bh(lock)
#define raw_spin_unlock(lock)		_raw_spin_unlock(lock)
#define raw_spin_unlock_irq(lock)	_raw_spin_unlock_irq(lock)

#define raw_spin_unlock_irqrestore(lock, flags)		\
	do {							\
		typecheck(unsigned long, flags);		\
		_raw_spin_unlock_irqrestore(lock, flags);	\
	} while (0)
#define raw_spin_unlock_bh(lock)	_raw_spin_unlock_bh(lock)

#define raw_spin_trylock_bh(lock) \
	__cond_lock(lock, _raw_spin_trylock_bh(lock))

#define raw_spin_trylock_irq(lock) \
({ \
	local_irq_disable(); \
	raw_spin_trylock(lock) ? \
	1 : ({ local_irq_enable(); 0;  }); \
})

#define raw_spin_can_lock(lock)	(!raw_spin_is_locked(lock))

#include <linux/rwlock.h>

# include <linux/spinlock_api_up.h>

static inline raw_spinlock_t *spinlock_check(spinlock_t *lock)
{
	return &lock->rlock;
}

static inline void spin_lock(spinlock_t *lock)
{
	raw_spin_lock(&lock->rlock);
}

static inline void spin_lock_bh(spinlock_t *lock)
{
	raw_spin_lock_bh(&lock->rlock);
}

static inline void spin_lock_irq(spinlock_t *lock)
{
	raw_spin_lock_irq(&lock->rlock);
}

#define spin_lock_irqsave(lock, flags)				\
do {								\
	raw_spin_lock_irqsave(spinlock_check(lock), flags);	\
} while (0)

static inline void spin_unlock(spinlock_t *lock)
{
	raw_spin_unlock(&lock->rlock);
}

static inline void spin_unlock_bh(spinlock_t *lock)
{
	raw_spin_unlock_bh(&lock->rlock);
}

static inline void spin_unlock_irq(spinlock_t *lock)
{
	raw_spin_unlock_irq(&lock->rlock);
}

static inline void spin_unlock_irqrestore(spinlock_t *lock, unsigned long flags)
{
	raw_spin_unlock_irqrestore(&lock->rlock, flags);
}

static inline int spin_is_contended(spinlock_t *lock)
{
	return raw_spin_is_contended(&lock->rlock);
}

#define assert_spin_locked(lock)	assert_raw_spin_locked(&(lock)->rlock)

#include <linux/atomic.h>

#endif /* ! __LINUX_SPINLOCK_H__ */
