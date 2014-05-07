#ifndef __ASM_MEMORY_H__
#define __ASM_MEMORY_H__

#include <linux/compiler.h>
#include <linux/const.h>
#include <linux/types.h>
#include <linux/sizes.h>

#include <mach/memory.h>

#define UL(x) _AC(x, UL)

#define PAGE_OFFSET		UL(CONFIG_PAGE_OFFSET)
#define TASK_SIZE		(UL(CONFIG_PAGE_OFFSET) - UL(SZ_16M))

#define MODULES_VADDR		(PAGE_OFFSET - SZ_16M)

#define	__phys_to_pfn(paddr)	((unsigned long)((paddr) >> PAGE_SHIFT))
#define	__pfn_to_phys(pfn)	((phys_addr_t)(pfn) << PAGE_SHIFT)

#define page_to_phys(page)	(__pfn_to_phys(page_to_pfn(page)))

#define __virt_to_phys(x)	((x) - PAGE_OFFSET + PHYS_OFFSET)
#define __phys_to_virt(x)	((x) - PHYS_OFFSET + PAGE_OFFSET)

#define PHYS_OFFSET	PLAT_PHYS_OFFSET

#define PHYS_PFN_OFFSET	(PHYS_OFFSET >> PAGE_SHIFT)

#define __pa(x)			__virt_to_phys((unsigned long)(x))
#define __va(x)			((void *)__phys_to_virt((unsigned long)(x)))

#define ARCH_PFN_OFFSET		PHYS_PFN_OFFSET

#define virt_to_page(kaddr)	pfn_to_page(__pa(kaddr) >> PAGE_SHIFT)

#include <asm-generic/memory_model.h>

#endif /* ! __ASM_MEMORY_H__ */
