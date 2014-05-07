#ifndef __LINUX_SPINLOCK_UP_H__
#define __LINUX_SPINLOCK_UP_H__

#include <asm/processor.h>	/* for cpu_relax() */

#define arch_spin_is_locked(lock)	((void)(lock), 0)

# define arch_spin_lock(lock)		do { barrier(); (void)(lock); } while (0)
# define arch_spin_lock_flags(lock, flags)	do { barrier(); (void)(lock); } while (0)
# define arch_spin_unlock(lock)	do { barrier(); (void)(lock); } while (0)
# define arch_spin_trylock(lock)	({ barrier(); (void)(lock); 1; })

#define arch_spin_is_contended(lock)	(((void)(lock), 0))

#define arch_spin_unlock_wait(lock) \
		do { cpu_relax(); } while (arch_spin_is_locked(lock))

#endif /* ! __LINUX_SPINLOCK_UP_H__ */
