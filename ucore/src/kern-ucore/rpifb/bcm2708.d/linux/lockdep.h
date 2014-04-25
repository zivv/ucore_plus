#ifndef __LINUX_LOCKDEP_H__
#define __LINUX_LOCKDEP_H__

struct task_struct;

# define lockdep_init_map(lock, name, key, sub) \
		do { (void)(name); (void)(key); } while (0)

struct lock_class_key { };

#endif /* ! __LINUX_LOCKDEP_H__ */
