#ifndef __LINUX_TYPES_H__
#define __LINUX_TYPES_H__

#include <uapi/linux/types.h>

#define DECLARE_BITMAP(name,bits) \
	unsigned long name[BITS_TO_LONGS(bits)]

typedef __u32 __kernel_dev_t;

typedef __kernel_dev_t		dev_t;

typedef unsigned short		umode_t;

typedef __kernel_pid_t		pid_t;

typedef __kernel_clockid_t	clockid_t;

//typedef _Bool			bool;
typedef int bool;

typedef __kernel_uid32_t	uid_t;
typedef __kernel_gid32_t	gid_t;

typedef __kernel_loff_t		loff_t;

typedef __kernel_size_t		size_t;

typedef __kernel_ssize_t	ssize_t;

typedef __kernel_time_t		time_t;

typedef __kernel_clock_t	clock_t;

typedef		__s32		int32_t;

typedef		__u32		uint32_t;

typedef u64 sector_t;
typedef u64 blkcnt_t;

#define pgoff_t unsigned long

typedef u32 dma_addr_t;

typedef unsigned __bitwise__ gfp_t;
typedef unsigned __bitwise__ fmode_t;
typedef unsigned __bitwise__ oom_flags_t;

typedef u32 phys_addr_t;

typedef phys_addr_t resource_size_t;

typedef struct {
	int counter;
} atomic_t;

struct list_head {
	struct list_head *next, *prev;
};

struct hlist_head {
	struct hlist_node *first;
};

struct hlist_node {
	struct hlist_node *next, **pprev;
};

struct callback_head {
	struct callback_head *next;
	void (*func)(struct callback_head *head);
};
#define rcu_head callback_head

#endif /* ! __LINUX_TYPES_H__ */
