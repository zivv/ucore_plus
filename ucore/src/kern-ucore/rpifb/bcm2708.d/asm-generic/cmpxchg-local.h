#ifndef __ASM_GENERIC_CMPXCHG_LOCAL_H__
#define __ASM_GENERIC_CMPXCHG_LOCAL_H__

#include <linux/types.h>
#include <linux/irqflags.h>

extern unsigned long wrong_size_cmpxchg(volatile void *ptr);

static inline unsigned long __cmpxchg_local_generic(volatile void *ptr,
		unsigned long old, unsigned long new, int size)
{
	unsigned long flags, prev;

	/*
	 * Sanity checking, compile-time.
	 */
	if (size == 8 && sizeof(unsigned long) != 8)
		wrong_size_cmpxchg(ptr);

	raw_local_irq_save(flags);
	switch (size) {
	case 1: prev = *(u8 *)ptr;
		if (prev == old)
			*(u8 *)ptr = (u8)new;
		break;
	case 2: prev = *(u16 *)ptr;
		if (prev == old)
			*(u16 *)ptr = (u16)new;
		break;
	case 4: prev = *(u32 *)ptr;
		if (prev == old)
			*(u32 *)ptr = (u32)new;
		break;
	case 8: prev = *(u64 *)ptr;
		if (prev == old)
			*(u64 *)ptr = (u64)new;
		break;
	default:
		wrong_size_cmpxchg(ptr);
	}
	raw_local_irq_restore(flags);
	return prev;
}

#endif /* ! __ASM_GENERIC_CMPXCHG_LOCAL_H__ */
