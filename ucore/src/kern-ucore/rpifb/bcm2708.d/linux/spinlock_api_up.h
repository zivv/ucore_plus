#ifndef __LINUX_SPINLOCK_API_UP_H__
#define __LINUX_SPINLOCK_API_UP_H__

#define assert_raw_spin_locked(lock)	do { (void)(lock); } while (0)

#define __LOCK(lock) \
  do { preempt_disable(); __acquire(lock); (void)(lock); } while (0)

#define __LOCK_BH(lock) \
  do { local_bh_disable(); __LOCK(lock); } while (0)

#define __LOCK_IRQ(lock) \
  do { local_irq_disable(); __LOCK(lock); } while (0)

#define __LOCK_IRQSAVE(lock, flags) \
  do { local_irq_save(flags); __LOCK(lock); } while (0)

#define __UNLOCK(lock) \
  do { preempt_enable(); __release(lock); (void)(lock); } while (0)

#define __UNLOCK_BH(lock) \
  do { preempt_enable_no_resched(); local_bh_enable(); \
	  __release(lock); (void)(lock); } while (0)

#define __UNLOCK_IRQ(lock) \
  do { local_irq_enable(); __UNLOCK(lock); } while (0)

#define __UNLOCK_IRQRESTORE(lock, flags) \
  do { local_irq_restore(flags); __UNLOCK(lock); } while (0)

#define _raw_spin_lock(lock)			__LOCK(lock)

#define _raw_spin_lock_bh(lock)			__LOCK_BH(lock)

#define _raw_spin_lock_irq(lock)		__LOCK_IRQ(lock)

#define _raw_spin_lock_irqsave(lock, flags)	__LOCK_IRQSAVE(lock, flags)

#define _raw_spin_trylock(lock)			({ __LOCK(lock); 1; })

#define _raw_spin_trylock_bh(lock)		({ __LOCK_BH(lock); 1; })
#define _raw_spin_unlock(lock)			__UNLOCK(lock)

#define _raw_spin_unlock_bh(lock)		__UNLOCK_BH(lock)

#define _raw_spin_unlock_irq(lock)		__UNLOCK_IRQ(lock)

#define _raw_spin_unlock_irqrestore(lock, flags) \
					__UNLOCK_IRQRESTORE(lock, flags)

#endif /* ! __LINUX_SPINLOCK_API_UP_H__ */
