#ifndef __ASM_GENERIC_PERCPU_H__
#define __ASM_GENERIC_PERCPU_H__

#include <linux/compiler.h>
#include <linux/threads.h>
#include <linux/percpu-defs.h>

#define VERIFY_PERCPU_PTR(__p) ({			\
	__verify_pcpu_ptr((__p));			\
	(typeof(*(__p)) __kernel __force *)(__p);	\
})

#define this_cpu_ptr(ptr)	per_cpu_ptr(ptr, 0)
#define __this_cpu_ptr(ptr)	this_cpu_ptr(ptr)

#define PER_CPU_BASE_SECTION ".data"

#define PER_CPU_ATTRIBUTES

#endif /* ! __ASM_GENERIC_PERCPU_H__ */
