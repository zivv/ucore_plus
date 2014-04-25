#ifndef __LINUX_KMEMCHECK_H__
#define __LINUX_KMEMCHECK_H__

#include <linux/mm_types.h>
#include <linux/types.h>

static inline void kmemcheck_mark_initialized(void *address, unsigned int n)
{
}

#endif /* ! __LINUX_KMEMCHECK_H__ */
