#ifndef __ASM_FPSTATE_H__
#define __ASM_FPSTATE_H__

struct vfp_hard_struct {
#ifdef CONFIG_VFPv3
	__u64 fpregs[32];
#else
	__u64 fpregs[16];
#endif
#if __LINUX_ARM_ARCH__ < 6
	__u32 fpmx_state;
#endif
	__u32 fpexc;
	__u32 fpscr;
	/*
	 * VFP implementation specific state
	 */
	__u32 fpinst;
	__u32 fpinst2;

#ifdef CONFIG_SMP
	__u32 cpu;
#endif
};

union vfp_state {
	struct vfp_hard_struct	hard;
};

#define FP_HARD_SIZE 35

struct fp_hard_struct {
	unsigned int save[FP_HARD_SIZE];		/* as yet undefined */
};

#define FP_SOFT_SIZE 35

struct fp_soft_struct {
	unsigned int save[FP_SOFT_SIZE];		/* undefined information */
};

#define IWMMXT_SIZE	0x98

union fp_state {
	struct fp_hard_struct	hard;
	struct fp_soft_struct	soft;
#ifdef CONFIG_IWMMXT
	struct iwmmxt_struct	iwmmxt;
#endif
};

#endif /* ! __ASM_FPSTATE_H__ */
