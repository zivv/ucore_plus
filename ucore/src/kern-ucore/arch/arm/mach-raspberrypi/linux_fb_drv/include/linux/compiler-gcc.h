#ifndef __LINUX_COMPILER_GCC_H__
#define __LINUX_COMPILER_GCC_H__

#define GCC_VERSION (__GNUC__ * 10000 \
		   + __GNUC_MINOR__ * 100 \
		   + __GNUC_PATCHLEVEL__)

#define barrier() __asm__ __volatile__("": : :"memory")

#define RELOC_HIDE(ptr, off)					\
  ({ unsigned long __ptr;					\
    __asm__ ("" : "=r"(__ptr) : "0"(ptr));		\
    (typeof(ptr)) (__ptr + (off)); })

#define __must_be_array(a) BUILD_BUG_ON_ZERO(__same_type((a), &(a)[0]))

# define inline		inline		__attribute__((always_inline)) notrace
# define __inline__	__inline__	__attribute__((always_inline)) notrace

#define __deprecated			__attribute__((deprecated))

#define __weak				__attribute__((weak))

#define __noreturn			__attribute__((noreturn))

#define __printf(a, b)			__attribute__((format(printf, a, b)))
#define __scanf(a, b)			__attribute__((format(scanf, a, b)))
#define  noinline			__attribute__((noinline))
#define __attribute_const__		__attribute__((__const__))
#define __maybe_unused			__attribute__((unused))
#define __always_unused			__attribute__((unused))

#define __gcc_header(x) #x
#define _gcc_header(x) __gcc_header(linux/compiler-gcc##x.h)
#define gcc_header(x) _gcc_header(x)
#include gcc_header(__GNUC__)

#define uninitialized_var(x) x = x

#define __always_inline		inline __attribute__((always_inline))

#endif /* ! __LINUX_COMPILER_GCC_H__ */
