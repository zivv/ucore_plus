#ifndef __LINUX_JUMP_LABEL_H__
#define __LINUX_JUMP_LABEL_H__

#include <linux/types.h>
#include <linux/compiler.h>
#include <linux/workqueue.h>

struct module;

#include <linux/atomic.h>

struct static_key {
	atomic_t enabled;
};

static inline void static_key_slow_dec(struct static_key *key)
{
	atomic_dec(&key->enabled);
}

#endif /* ! __LINUX_JUMP_LABEL_H__ */
