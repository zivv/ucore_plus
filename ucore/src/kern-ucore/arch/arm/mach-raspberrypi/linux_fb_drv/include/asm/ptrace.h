#ifndef __ASM_PTRACE_H__
#define __ASM_PTRACE_H__

#include <uapi/asm/ptrace.h>

#include <linux/stddef.h>
#include <linux/types.h>
#define MAX_REG_OFFSET (offsetof(struct pt_regs, ARM_ORIG_r0))

#define current_pt_regs(void) ({				\
	register unsigned long sp asm ("sp");			\
	(struct pt_regs *)((sp | (THREAD_SIZE - 1)) - 7) - 1;	\
})

#endif /* ! __ASM_PTRACE_H__ */
