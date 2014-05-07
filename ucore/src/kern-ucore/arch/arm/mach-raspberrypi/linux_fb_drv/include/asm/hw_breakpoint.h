#ifndef __ASM_HW_BREAKPOINT_H__
#define __ASM_HW_BREAKPOINT_H__

struct task_struct;

#define ARM_MAX_BRP		16
#define ARM_MAX_WRP		16
#define ARM_MAX_HBP_SLOTS	(ARM_MAX_BRP + ARM_MAX_WRP)

struct perf_event;

#endif /* ! __ASM_HW_BREAKPOINT_H__ */
