#ifndef __LINUX_PERCPU_COUNTER_H__
#define __LINUX_PERCPU_COUNTER_H__

#include <linux/spinlock.h>
#include <linux/smp.h>
#include <linux/list.h>
#include <linux/threads.h>
#include <linux/percpu.h>
#include <linux/types.h>

struct percpu_counter {
	s64 count;
};

static inline void
percpu_counter_add(struct percpu_counter *fbc, s64 amount)
{
	preempt_disable();
	fbc->count += amount;
	preempt_enable();
}

static inline s64 percpu_counter_read(struct percpu_counter *fbc)
{
	return fbc->count;
}

static inline s64 percpu_counter_read_positive(struct percpu_counter *fbc)
{
	return fbc->count;
}

static inline void percpu_counter_inc(struct percpu_counter *fbc)
{
	percpu_counter_add(fbc, 1);
}

static inline void percpu_counter_dec(struct percpu_counter *fbc)
{
	percpu_counter_add(fbc, -1);
}

#endif /* ! __LINUX_PERCPU_COUNTER_H__ */
