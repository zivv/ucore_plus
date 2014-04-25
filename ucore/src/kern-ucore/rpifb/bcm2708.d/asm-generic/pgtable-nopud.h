#ifndef __ASM_GENERIC_PGTABLE_NOPUD_H__
#define __ASM_GENERIC_PGTABLE_NOPUD_H__

#define __PAGETABLE_PUD_FOLDED

typedef struct { pgd_t pgd; } pud_t;

static inline int pgd_none(pgd_t pgd)		{ return 0; }
static inline int pgd_bad(pgd_t pgd)		{ return 0; }

static inline pud_t * pud_offset(pgd_t * pgd, unsigned long address)
{
	return (pud_t *)pgd;
}

#define pud_addr_end(addr, end)			(end)

#endif /* ! __ASM_GENERIC_PGTABLE_NOPUD_H__ */
