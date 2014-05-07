#ifndef __LINUX_KOBJECT_NS_H__
#define __LINUX_KOBJECT_NS_H__

struct sock;
struct kobject;

enum kobj_ns_type {
	KOBJ_NS_TYPE_NONE = 0,
	KOBJ_NS_TYPE_NET,
	KOBJ_NS_TYPES
};

struct kobj_ns_type_operations {
	enum kobj_ns_type type;
	void *(*grab_current_ns)(void);
	const void *(*netlink_ns)(struct sock *sk);
	const void *(*initial_ns)(void);
	void (*drop_ns)(void *);
};

#endif /* ! __LINUX_KOBJECT_NS_H__ */
