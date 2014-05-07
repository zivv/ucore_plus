#ifndef __LINUX_ATOMIC_H__
#define __LINUX_ATOMIC_H__

#include <asm/atomic.h>

static inline int atomic_add_unless(atomic_t *v, int a, int u)
{
	return __atomic_add_unless(v, a, u) != u;
}

#define atomic_inc_not_zero(v)		atomic_add_unless((v), 1, 0)

static inline int atomic_inc_unless_negative(atomic_t *p)
{
	int v, v1;
	for (v = 0; v >= 0; v = v1) {
		v1 = atomic_cmpxchg(p, v, v + 1);
		if (likely(v1 == v))
			return 1;
	}
	return 0;
}

static inline int atomic_dec_unless_positive(atomic_t *p)
{
	int v, v1;
	for (v = 0; v <= 0; v = v1) {
		v1 = atomic_cmpxchg(p, v, v - 1);
		if (likely(v1 == v))
			return 1;
	}
	return 0;
}

#include <asm-generic/atomic-long.h>

#include <asm-generic/atomic64.h>

#endif /* ! __LINUX_ATOMIC_H__ */
