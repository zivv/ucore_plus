#ifndef __ASM_MODULE_H__
#define __ASM_MODULE_H__

#include <asm-generic/module.h>

struct unwind_table;

enum {
	ARM_SEC_INIT,
	ARM_SEC_DEVINIT,
	ARM_SEC_CORE,
	ARM_SEC_EXIT,
	ARM_SEC_DEVEXIT,
	ARM_SEC_MAX,
};

struct mod_arch_specific {
	struct unwind_table *unwind[ARM_SEC_MAX];
};

#endif /* ! __ASM_MODULE_H__ */
