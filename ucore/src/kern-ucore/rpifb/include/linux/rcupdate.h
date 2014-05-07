#ifndef __LINUX_RCUPDATE_H__
#define __LINUX_RCUPDATE_H__

#include <linux/types.h>
#include <linux/cache.h>
#include <linux/spinlock.h>
#include <linux/threads.h>
#include <linux/cpumask.h>
#include <linux/seqlock.h>
#include <linux/lockdep.h>
#include <linux/completion.h>
#include <linux/debugobjects.h>
#include <linux/bug.h>
#include <linux/compiler.h>

extern void synchronize_sched(void);

extern void __rcu_read_lock(void);
extern void __rcu_read_unlock(void);

#include <linux/rcutree.h>

# define rcu_lock_acquire(a)		do { } while (0)
# define rcu_lock_release(a)		do { } while (0)

#define rcu_lockdep_assert(c, s) do { } while (0)

#define rcu_dereference_sparse(p, space)

#define __rcu_dereference_check(p, c, space) \
	({ \
		typeof(*p) *_________p1 = (typeof(*p)*__force )ACCESS_ONCE(p); \
		rcu_lockdep_assert(c, "suspicious rcu_dereference_check()" \
				      " usage"); \
		rcu_dereference_sparse(p, space); \
		smp_read_barrier_depends(); \
		((typeof(*p) __force __kernel *)(_________p1)); \
	})
#define __rcu_dereference_protected(p, c, space) \
	({ \
		rcu_lockdep_assert(c, "suspicious rcu_dereference_protected()" \
				      " usage"); \
		rcu_dereference_sparse(p, space); \
		((typeof(*p) __force __kernel *)(p)); \
	})

#define __rcu_assign_pointer(p, v, space) \
	do { \
		smp_wmb(); \
		(p) = (typeof(*v) __force space *)(v); \
	} while (0)

#define rcu_dereference_check(p, c) \
	__rcu_dereference_check((p), rcu_read_lock_held() || (c), __rcu)

#define rcu_dereference_raw(p) rcu_dereference_check(p, 1) /*@@@ needed? @@@*/

#define rcu_dereference_protected(p, c) \
	__rcu_dereference_protected((p), (c), __rcu)

#define rcu_dereference(p) rcu_dereference_check(p, 0)

#define rcu_assign_pointer(p, v) \
	__rcu_assign_pointer((p), (v), __rcu)

#endif /* ! __LINUX_RCUPDATE_H__ */
