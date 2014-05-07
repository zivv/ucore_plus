#ifndef __LINUX_ERR_H__
#define __LINUX_ERR_H__

#include <linux/compiler.h>

#include <asm/errno.h>

#define MAX_ERRNO	4095

#define IS_ERR_VALUE(x) unlikely((x) >= (unsigned long)-MAX_ERRNO)

static inline void * __must_check ERR_PTR(long error)
{
	return (void *) error;
}

static inline long __must_check PTR_ERR(const void *ptr)
{
	return (long) ptr;
}

static inline long __must_check IS_ERR(const void *ptr)
{
	return IS_ERR_VALUE((unsigned long)ptr);
}

#endif /* ! __LINUX_ERR_H__ */
