#ifndef __LINUX_SMP_H__
#define __LINUX_SMP_H__

#include <linux/errno.h>
#include <linux/types.h>
#include <linux/list.h>
#include <linux/cpumask.h>
#include <linux/init.h>
#include <linux/irqflags.h>

typedef void (*smp_call_func_t)(void *info);

int smp_call_function_single(int cpuid, smp_call_func_t func, void *info,
			     int wait);

#define raw_smp_processor_id()			0

#endif /* ! __LINUX_SMP_H__ */
