#ifndef __LINUX_INTERRUPT_H__
#define __LINUX_INTERRUPT_H__

#include <linux/kernel.h>
#include <linux/linkage.h>
#include <linux/bitops.h>
#include <linux/preempt.h>
#include <linux/cpumask.h>
#include <linux/irqreturn.h>
#include <linux/irqnr.h>
#include <linux/hardirq.h>
#include <linux/irqflags.h>
#include <linux/smp.h>
#include <linux/percpu.h>
#include <linux/hrtimer.h>
#include <linux/kref.h>
#include <linux/workqueue.h>

#include <linux/atomic.h>
#include <asm/ptrace.h>

typedef irqreturn_t (*irq_handler_t)(int, void *);

extern int __must_check
request_threaded_irq(unsigned int irq, irq_handler_t handler,
		     irq_handler_t thread_fn,
		     unsigned long flags, const char *name, void *dev);

static inline int __must_check
request_irq(unsigned int irq, irq_handler_t handler, unsigned long flags,
	    const char *name, void *dev)
{
	return request_threaded_irq(irq, handler, NULL, flags, name, dev);
}

extern void free_irq(unsigned int, void *);

struct device;

extern int __must_check
devm_request_threaded_irq(struct device *dev, unsigned int irq,
			  irq_handler_t handler, irq_handler_t thread_fn,
			  unsigned long irqflags, const char *devname,
			  void *dev_id);

extern void disable_irq_nosync(unsigned int irq);
extern void disable_irq(unsigned int irq);

extern void enable_irq(unsigned int irq);

extern int irq_set_irq_wake(unsigned int irq, unsigned int on);

DECLARE_PER_CPU(struct task_struct *, ksoftirqd);

struct tasklet_struct
{
	struct tasklet_struct *next;
	unsigned long state;
	atomic_t count;
	void (*func)(unsigned long);
	unsigned long data;
};

#define tasklet_unlock_wait(t) do { } while (0)

extern void __tasklet_schedule(struct tasklet_struct *t);

extern void __tasklet_hi_schedule(struct tasklet_struct *t);

extern void __tasklet_hi_schedule_first(struct tasklet_struct *t);

static inline void tasklet_disable_nosync(struct tasklet_struct *t)
{
	atomic_inc(&t->count);
	smp_mb__after_atomic_inc();
}

extern void tasklet_kill(struct tasklet_struct *t);

struct seq_file;

#endif /* ! __LINUX_INTERRUPT_H__ */
