#ifndef __ASM_THREAD_INFO_H__
#define __ASM_THREAD_INFO_H__

#include <linux/compiler.h>
#include <asm/fpstate.h>

#define THREAD_SIZE		8192

struct task_struct;
struct exec_domain;

#include <asm/types.h>
#include <asm/domain.h>

typedef unsigned long mm_segment_t;

struct cpu_context_save {
	__u32	r4;
	__u32	r5;
	__u32	r6;
	__u32	r7;
	__u32	r8;
	__u32	r9;
	__u32	sl;
	__u32	fp;
	__u32	sp;
	__u32	pc;
	__u32	extra[2];		/* Xscale 'acc' register, etc */
};

struct thread_info {
	unsigned long		flags;		/* low level flags */
	int			preempt_count;	/* 0 => preemptable, <0 => bug */
	mm_segment_t		addr_limit;	/* address limit */
	struct task_struct	*task;		/* main task structure */
	struct exec_domain	*exec_domain;	/* execution domain */
	__u32			cpu;		/* cpu */
	__u32			cpu_domain;	/* cpu domain */
	struct cpu_context_save	cpu_context;	/* cpu context */
	__u32			syscall;	/* syscall number */
	__u8			used_cp[16];	/* thread used copro */
	unsigned long		tp_value;
#ifdef CONFIG_CRUNCH
	struct crunch_state	crunchstate;
#endif
	union fp_state		fpstate __attribute__((aligned(8)));
	union vfp_state		vfpstate;
#ifdef CONFIG_ARM_THUMBEE
	unsigned long		thumbee_state;	/* ThumbEE Handler Base register */
#endif
	struct restart_block	restart_block;
};

static inline struct thread_info *current_thread_info(void) __attribute_const__;

static inline struct thread_info *current_thread_info(void)
{
	register unsigned long sp asm ("sp");
	return (struct thread_info *)(sp & ~(THREAD_SIZE - 1));
}

#define PREEMPT_ACTIVE	0x40000000

#define TIF_SIGPENDING		0
#define TIF_NEED_RESCHED	1

#define TIF_SECCOMP		11	/* seccomp syscall filtering active */

#define TIF_RESTORE_SIGMASK	20

#endif /* ! __ASM_THREAD_INFO_H__ */
