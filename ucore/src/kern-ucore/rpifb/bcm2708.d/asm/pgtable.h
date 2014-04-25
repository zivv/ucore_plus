#ifndef __ASM_PGTABLE_H__
#define __ASM_PGTABLE_H__

#include <linux/const.h>
#include <asm/proc-fns.h>

#include <asm-generic/pgtable-nopud.h>
#include <asm/memory.h>
#include <asm/pgtable-hwdef.h>

#include <asm/pgtable-2level.h>

#define VMALLOC_OFFSET		(8*1024*1024)
#define VMALLOC_START		(((unsigned long)high_memory + VMALLOC_OFFSET) & ~(VMALLOC_OFFSET-1))
#define VMALLOC_END		0xff000000UL

#define pgprot_noncached(prot) \
	__pgprot_modify(prot, L_PTE_MT_MASK, L_PTE_MT_UNCACHED)

#define pgprot_writecombine(prot) \
	__pgprot_modify(prot, L_PTE_MT_MASK, L_PTE_MT_BUFFERABLE)

struct file;

#define pmd_none(pmd)		(!pmd_val(pmd))

#define pte_clear(mm,addr,ptep)	set_pte_ext(ptep, __pte(0), 0)

#define pte_present(pte)	(pte_val(pte) & L_PTE_PRESENT)

#define pte_young(pte)		(pte_val(pte) & L_PTE_YOUNG)

#define pte_present_user(pte)  (pte_present(pte) && (pte_val(pte) & L_PTE_USER))

static inline void __sync_icache_dcache(pte_t pteval)
{
}

static inline void set_pte_at(struct mm_struct *mm, unsigned long addr,
			      pte_t *ptep, pte_t pteval)
{
	unsigned long ext = 0;

	if (addr < TASK_SIZE && pte_present_user(pteval)) {
		__sync_icache_dcache(pteval);
		ext |= PTE_EXT_NG;
	}

	set_pte_ext(ptep, pteval, ext);
}

#define PTE_BIT_FUNC(fn,op) \
static inline pte_t pte_##fn(pte_t pte) { pte_val(pte) op; return pte; }

PTE_BIT_FUNC(wrprotect, |= L_PTE_RDONLY);
PTE_BIT_FUNC(mkwrite,   &= ~L_PTE_RDONLY);

PTE_BIT_FUNC(mkold,     &= ~L_PTE_YOUNG);

#include <asm-generic/pgtable.h>

#endif /* ! __ASM_PGTABLE_H__ */
