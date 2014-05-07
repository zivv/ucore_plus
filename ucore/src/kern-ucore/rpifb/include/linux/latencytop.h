#ifndef __LINUX_LATENCYTOP_H__
#define __LINUX_LATENCYTOP_H__

#include <linux/compiler.h>
struct task_struct;

#define LT_SAVECOUNT		32
#define LT_BACKTRACEDEPTH	12

struct latency_record {
	unsigned long	backtrace[LT_BACKTRACEDEPTH];
	unsigned int	count;
	unsigned long	time;
	unsigned long	max;
};

extern int latencytop_enabled;
void __account_scheduler_latency(struct task_struct *task, int usecs, int inter);

#endif /* ! __LINUX_LATENCYTOP_H__ */
