#ifndef __ASM_PAGE_H__
#define __ASM_PAGE_H__

#define PAGE_SHIFT		12
#define PAGE_SIZE		(_AC(1,UL) << PAGE_SHIFT)
#define PAGE_MASK		(~(PAGE_SIZE-1))

#include <asm/glue.h>

# define MULTI_USER 1

struct page;
struct vm_area_struct;

#define __HAVE_ARCH_GATE_AREA 1

#include <asm/pgtable-2level-types.h>

#include <asm/memory.h>

#include <asm-generic/getorder.h>

#endif /* ! __ASM_PAGE_H__ */
