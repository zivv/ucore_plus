#ifndef __LINUX_KREF_H__
#define __LINUX_KREF_H__

#include <linux/bug.h>
#include <linux/atomic.h>
#include <linux/kernel.h>
#include <linux/mutex.h>
#include <linux/spinlock.h>

struct kref {
	atomic_t refcount;
};

static inline int kref_sub(struct kref *kref, unsigned int count,
	     void (*release)(struct kref *kref))
{
	WARN_ON(release == NULL);

	if (atomic_sub_and_test((int) count, &kref->refcount)) {
		release(kref);
		return 1;
	}
	return 0;
}

#endif /* ! __LINUX_KREF_H__ */
