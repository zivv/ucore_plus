#ifndef __ASM_PROC_FNS_H__
#define __ASM_PROC_FNS_H__

#include <asm/glue-proc.h>
#include <asm/page.h>

struct mm_struct;

extern void cpu_set_pte_ext(pte_t *ptep, pte_t pte, unsigned int ext);

#include <asm/memory.h>

#endif /* ! __ASM_PROC_FNS_H__ */
