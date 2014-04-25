#ifndef __ASM_GENERIC_BITOPS_ARCH_HWEIGHT_H__
#define __ASM_GENERIC_BITOPS_ARCH_HWEIGHT_H__

#include <asm/types.h>

static inline unsigned int __arch_hweight32(unsigned int w)
{
	return __sw_hweight32(w);
}

static inline unsigned long __arch_hweight64(__u64 w)
{
	return __sw_hweight64(w);
}

#endif /* ! __ASM_GENERIC_BITOPS_ARCH_HWEIGHT_H__ */
