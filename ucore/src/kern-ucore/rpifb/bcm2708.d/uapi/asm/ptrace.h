#ifndef __UAPI_ASM_PTRACE_H__
#define __UAPI_ASM_PTRACE_H__

#include <asm/hwcap.h>

#define USR26_MODE	0x00000000

#define USR_MODE	0x00000010

#define MODE32_BIT	0x00000010
#define MODE_MASK	0x0000001f
#define PSR_T_BIT	0x00000020
#define PSR_F_BIT	0x00000040
#define PSR_I_BIT	0x00000080
#define PSR_A_BIT	0x00000100

#define PSR_f		0xff000000	/* Flags		*/
#define PSR_s		0x00ff0000	/* Status		*/
#define PSR_x		0x0000ff00	/* Extension		*/

#define ARM_cpsr	uregs[16]

#define ARM_sp		uregs[13]

#define ARM_r0		uregs[0]
#define ARM_ORIG_r0	uregs[17]

#endif /* ! __UAPI_ASM_PTRACE_H__ */
