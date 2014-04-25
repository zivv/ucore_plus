#ifndef __LINUX_INIT_H__
#define __LINUX_INIT_H__

#include <linux/compiler.h>
#include <linux/types.h>

#define __init		__section(.init.text) __cold notrace
#define __initdata	__section(.init.data)

#define __exit_call	__used __section(.exitcall.exit)

#define __exitused  __used

#define __exit          __section(.exit.text) __exitused __cold notrace

#define __meminit        __section(.meminit.text) __cold notrace

typedef int (*initcall_t)(void);
typedef void (*exitcall_t)(void);

#define __define_initcall(fn, id) \
	static initcall_t __initcall_##fn##id __used \
	__attribute__((__section__(".initcall" #id ".init"))) = fn

#define device_initcall(fn)		__define_initcall(fn, 6)

#define __initcall(fn) device_initcall(fn)

#define __exitcall(fn) \
	static exitcall_t __exitcall_##fn __exit_call = fn

#define module_init(x)	__initcall(x);

#define module_exit(x)	__exitcall(x);

#endif /* ! __LINUX_INIT_H__ */
