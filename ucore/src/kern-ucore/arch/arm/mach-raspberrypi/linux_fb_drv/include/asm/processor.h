#ifndef __ASM_PROCESSOR_H__
#define __ASM_PROCESSOR_H__

#include <asm/hw_breakpoint.h>
#include <asm/ptrace.h>
#include <asm/types.h>

struct debug_info {
#ifdef CONFIG_HAVE_HW_BREAKPOINT
	struct perf_event	*hbp[ARM_MAX_HBP_SLOTS];
#endif
};

struct thread_struct {
							/* fault info	  */
	unsigned long		address;
	unsigned long		trap_no;
	unsigned long		error_code;
							/* debugging	  */
	struct debug_info	debug;
};

struct task_struct;

#define cpu_relax()			barrier()

#endif /* ! __ASM_PROCESSOR_H__ */
