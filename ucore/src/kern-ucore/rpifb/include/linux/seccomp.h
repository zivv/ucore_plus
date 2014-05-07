#ifndef __LINUX_SECCOMP_H__
#define __LINUX_SECCOMP_H__

#include <uapi/linux/seccomp.h>

#include <linux/thread_info.h>
#include <asm/seccomp.h>

struct seccomp_filter;

struct seccomp {
	int mode;
	struct seccomp_filter *filter;
};

extern int __secure_computing(int);
static inline int secure_computing(int this_syscall)
{
	if (unlikely(test_thread_flag(TIF_SECCOMP)))
		return  __secure_computing(this_syscall);
	return 0;
}

#endif /* ! __LINUX_SECCOMP_H__ */
