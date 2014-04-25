#ifndef __ASM_PGTABLE_2LEVEL_TYPES_H__
#define __ASM_PGTABLE_2LEVEL_TYPES_H__

#include <asm/types.h>

typedef u32 pteval_t;
typedef u32 pmdval_t;

typedef pteval_t pte_t;
typedef pmdval_t pmd_t;
typedef pmdval_t pgd_t[2];
typedef pteval_t pgprot_t;

#define pte_val(x)      (x)
#define pmd_val(x)      (x)

#define pgprot_val(x)   (x)

#define __pte(x)        (x)

#endif /* ! __ASM_PGTABLE_2LEVEL_TYPES_H__ */
