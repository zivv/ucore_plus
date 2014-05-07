#ifndef __ASM_GENERIC_ATOMIC_LONG_H__
#define __ASM_GENERIC_ATOMIC_LONG_H__

#include <asm/types.h>

typedef atomic_t atomic_long_t;

static inline long atomic_long_read(atomic_long_t *l)
{
	atomic_t *v = (atomic_t *)l;

	return (long)atomic_read(v);
}

static inline void atomic_long_inc(atomic_long_t *l)
{
	atomic_t *v = (atomic_t *)l;

	atomic_inc(v);
}

static inline void atomic_long_dec(atomic_long_t *l)
{
	atomic_t *v = (atomic_t *)l;

	atomic_dec(v);
}

static inline void atomic_long_add(long i, atomic_long_t *l)
{
	atomic_t *v = (atomic_t *)l;

	atomic_add(i, v);
}

#endif /* ! __ASM_GENERIC_ATOMIC_LONG_H__ */
