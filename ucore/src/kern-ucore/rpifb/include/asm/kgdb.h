#ifndef __ASM_KGDB_H__
#define __ASM_KGDB_H__

#include <linux/ptrace.h>

#define BREAK_INSTR_SIZE	4

#define DBG_MAX_REG_NUM		(_GP_REGS + _FP_REGS + _EXTRA_REGS)

#endif /* ! __ASM_KGDB_H__ */
