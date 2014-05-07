#ifndef __LINUX_COMPLETION_H__
#define __LINUX_COMPLETION_H__

#include <linux/wait.h>

struct completion {
	unsigned int done;
	wait_queue_head_t wait;
};

#endif /* ! __LINUX_COMPLETION_H__ */
