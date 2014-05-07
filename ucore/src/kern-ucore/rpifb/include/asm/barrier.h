#ifndef __ASM_BARRIER_H__
#define __ASM_BARRIER_H__

#include <asm/outercache.h>

#define isb() __asm__ __volatile__ ("" : : : "memory")
#define dsb() __asm__ __volatile__ ("mcr p15, 0, %0, c7, c10, 4" \
				    : : "r" (0) : "memory")

#define mb()		do { dsb(); outer_sync(); } while (0)
#define rmb()		dsb()
#define wmb()		mb()

#define smp_mb()	barrier()
#define smp_rmb()	barrier()
#define smp_wmb()	barrier()

#define smp_read_barrier_depends()	do { } while(0)

#endif /* ! __ASM_BARRIER_H__ */
