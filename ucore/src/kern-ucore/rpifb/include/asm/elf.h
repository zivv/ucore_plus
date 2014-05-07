#ifndef __ASM_ELF_H__
#define __ASM_ELF_H__

#include <asm/hwcap.h>

#include <asm/ptrace.h>
#include <asm/user.h>

struct task_struct;

#define ELF_NGREG (sizeof (struct pt_regs) / sizeof(elf_greg_t))

#define ELF_CLASS	ELFCLASS32

#define elf_read_implies_exec(ex,stk) arm_elf_read_implies_exec(&(ex), stk)

struct task_struct;

#define SET_PERSONALITY(ex)	elf_set_personality(&(ex))

struct mm_struct;

#endif /* ! __ASM_ELF_H__ */
