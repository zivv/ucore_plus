#ifndef __LINUX_CACHE_H__
#define __LINUX_CACHE_H__

#include <linux/kernel.h>
#include <asm/cache.h>

#define SMP_CACHE_BYTES L1_CACHE_BYTES

#define ____cacheline_aligned __attribute__((__aligned__(SMP_CACHE_BYTES)))

#define ____cacheline_aligned_in_smp

#define ____cacheline_internodealigned_in_smp

#endif /* ! __LINUX_CACHE_H__ */
