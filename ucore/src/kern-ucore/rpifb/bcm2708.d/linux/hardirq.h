#ifndef __LINUX_HARDIRQ_H__
#define __LINUX_HARDIRQ_H__

#include <linux/preempt.h>
#include <linux/lockdep.h>
#include <linux/ftrace_irq.h>
#include <linux/vtime.h>
#include <asm/hardirq.h>

#define PREEMPT_BITS	8
#define SOFTIRQ_BITS	8
#define NMI_BITS	1

#define MAX_HARDIRQ_BITS 10

# define HARDIRQ_BITS	MAX_HARDIRQ_BITS

#define PREEMPT_SHIFT	0
#define SOFTIRQ_SHIFT	(PREEMPT_SHIFT + PREEMPT_BITS)
#define HARDIRQ_SHIFT	(SOFTIRQ_SHIFT + SOFTIRQ_BITS)
#define NMI_SHIFT	(HARDIRQ_SHIFT + HARDIRQ_BITS)

#endif /* ! __LINUX_HARDIRQ_H__ */
