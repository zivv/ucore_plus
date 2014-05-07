#ifndef __LINUX_PTRACE_H__
#define __LINUX_PTRACE_H__

#include <linux/compiler.h>		/* For unlikely.  */
#include <linux/sched.h>		/* For struct task_struct.  */
#include <linux/err.h>			/* for IS_ERR_VALUE */
#include <linux/bug.h>			/* For BUG_ON.  */
#include <uapi/linux/ptrace.h>

#define PT_SEIZED	0x00010000	/* SEIZE used, enable new behavior */
#define PT_PTRACED	0x00000001

#define PT_OPT_FLAG_SHIFT	3

#define PT_EVENT_FLAG(event)	(1 << (PT_OPT_FLAG_SHIFT + (event)))

extern void ptrace_notify(int exit_code);
extern void __ptrace_link(struct task_struct *child,
			  struct task_struct *new_parent);
extern void __ptrace_unlink(struct task_struct *child);

static inline void ptrace_unlink(struct task_struct *child)
{
	if (unlikely(child->ptrace))
		__ptrace_unlink(child);
}

static inline bool ptrace_event_enabled(struct task_struct *task, int event)
{
	return task->ptrace & PT_EVENT_FLAG(event);
}

#endif /* ! __LINUX_PTRACE_H__ */
