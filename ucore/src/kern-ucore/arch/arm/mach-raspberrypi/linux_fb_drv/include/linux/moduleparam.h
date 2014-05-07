#ifndef __LINUX_MODULEPARAM_H__
#define __LINUX_MODULEPARAM_H__

#include <linux/init.h>
#include <linux/stringify.h>
#include <linux/kernel.h>

#define MODULE_PARAM_PREFIX KBUILD_MODNAME "."

#define MAX_PARAM_PREFIX_LEN (64 - sizeof(unsigned long))

#define __MODULE_INFO(tag, name, info)					  \
  struct __UNIQUE_ID(name) {}

#define __MODULE_PARM_TYPE(name, _type)					  \
  __MODULE_INFO(parmtype, name##type, #name ":" _type)

#define MODULE_PARM_DESC(_parm, desc) \
	__MODULE_INFO(parm, _parm, #_parm ":" desc)

struct kernel_param;

struct kernel_param_ops {
	/* Returns 0, or -errno.  arg is in kp->arg. */
	int (*set)(const char *val, const struct kernel_param *kp);
	/* Returns length written or -errno.  Buffer is 4k (ie. be short!) */
	int (*get)(char *buffer, const struct kernel_param *kp);
	/* Optional function to free kp->arg when module unloaded. */
	void (*free)(void *arg);
};

struct kernel_param {
	const char *name;
	const struct kernel_param_ops *ops;
	u16 perm;
	s16 level;
	union {
		void *arg;
		const struct kparam_string *str;
		const struct kparam_array *arr;
	};
};

struct kparam_string {
	unsigned int maxlen;
	char *string;
};

struct kparam_array
{
	unsigned int max;
	unsigned int elemsize;
	unsigned int *num;
	const struct kernel_param_ops *ops;
	void *elem;
};

#define module_param(name, type, perm)				\
	module_param_named(name, name, type, perm)

#define module_param_named(name, value, type, perm)			   \
	param_check_##type(name, &(value));				   \
	module_param_cb(name, &param_ops_##type, &value, perm);		   \
	__MODULE_PARM_TYPE(name, #type)

#define module_param_cb(name, ops, arg, perm)				      \
	__module_param_call(MODULE_PARAM_PREFIX, name, ops, arg, perm, -1)

#define __moduleparam_const const

#define __module_param_call(prefix, name, ops, arg, perm, level)	\
	/* Default value instead of permissions? */			\
	static int __param_perm_check_##name __attribute__((unused)) =	\
	BUILD_BUG_ON_ZERO((perm) < 0 || (perm) > 0777 || ((perm) & 2))	\
	+ BUILD_BUG_ON_ZERO(sizeof(""prefix) > MAX_PARAM_PREFIX_LEN);	\
	static const char __param_str_##name[] = prefix #name;		\
	static struct kernel_param __moduleparam_const __param_##name	\
	__used								\
    __attribute__ ((unused,__section__ ("__param"),aligned(sizeof(void *)))) \
	= { __param_str_##name, ops, perm, level, { arg } }

#define __param_check(name, p, type) \
	static inline type *__check_##name(void) { return(p); }

extern struct kernel_param_ops param_ops_int;

#define param_check_int(name, p) __param_check(name, p, int)

struct module;

#endif /* ! __LINUX_MODULEPARAM_H__ */
