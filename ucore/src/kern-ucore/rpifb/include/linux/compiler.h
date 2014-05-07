#ifndef __LINUX_COMPILER_H__
#define __LINUX_COMPILER_H__

#define __LINUX_COMPILER_H

# define __user
# define __kernel

# define __force
# define __nocast
# define __iomem

# define __acquires(x)
# define __releases(x)
# define __acquire(x) (void)0
# define __release(x) (void)0
# define __cond_lock(x,c) (c)
# define __percpu
# define __rcu

#define ___PASTE(a,b) a##b
#define __PASTE(a,b) ___PASTE(a,b)

#include <linux/compiler-gcc.h>

#define notrace __attribute__((no_instrument_function))

# define likely(x)	__builtin_expect(!!(x), 1)
# define unlikely(x)	__builtin_expect(!!(x), 0)

# define unreachable() do { } while (1)

# define __UNIQUE_ID(prefix) __PASTE(__PASTE(__UNIQUE_ID_, prefix), __LINE__)

#define __cold

# define __section(S) __attribute__ ((__section__(#S)))

# define __same_type(a, b) __builtin_types_compatible_p(typeof(a), typeof(b))

#define ACCESS_ONCE(x) (*(volatile typeof(x) *)&(x))

#endif /* ! __LINUX_COMPILER_H__ */
