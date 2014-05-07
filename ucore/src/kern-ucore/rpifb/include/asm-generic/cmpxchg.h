#ifndef __ASM_GENERIC_CMPXCHG_H__
#define __ASM_GENERIC_CMPXCHG_H__

#include <linux/types.h>
#include <linux/irqflags.h>

#include <asm-generic/cmpxchg-local.h>

#define cmpxchg(ptr, o, n)	cmpxchg_local((ptr), (o), (n))

#endif /* ! __ASM_GENERIC_CMPXCHG_H__ */
