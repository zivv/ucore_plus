#ifndef __LINUX_PERCPU_H__
#define __LINUX_PERCPU_H__

#include <linux/preempt.h>
#include <linux/smp.h>
#include <linux/cpumask.h>
#include <linux/pfn.h>
#include <linux/init.h>

#include <asm/percpu.h>

#define per_cpu_ptr(ptr, cpu)	({ (void)(cpu); VERIFY_PERCPU_PTR((ptr)); })

extern void __bad_size_call_parameter(void);

#define __pcpu_size_call_return(stem, variable)				\
({	typeof(variable) pscr_ret__;					\
	__verify_pcpu_ptr(&(variable));					\
	switch(sizeof(variable)) {					\
	case 1: pscr_ret__ = stem##1(variable);break;			\
	case 2: pscr_ret__ = stem##2(variable);break;			\
	case 4: pscr_ret__ = stem##4(variable);break;			\
	case 8: pscr_ret__ = stem##8(variable);break;			\
	default:							\
		__bad_size_call_parameter();break;			\
	}								\
	pscr_ret__;							\
})

#define __pcpu_size_call(stem, variable, ...)				\
do {									\
	__verify_pcpu_ptr(&(variable));					\
	switch(sizeof(variable)) {					\
		case 1: stem##1(variable, __VA_ARGS__);break;		\
		case 2: stem##2(variable, __VA_ARGS__);break;		\
		case 4: stem##4(variable, __VA_ARGS__);break;		\
		case 8: stem##8(variable, __VA_ARGS__);break;		\
		default: 						\
			__bad_size_call_parameter();break;		\
	}								\
} while (0)

#define _this_cpu_generic_read(pcp)					\
({	typeof(pcp) ret__;						\
	preempt_disable();						\
	ret__ = *this_cpu_ptr(&(pcp));					\
	preempt_enable();						\
	ret__;								\
})

#  define this_cpu_read_1(pcp)	_this_cpu_generic_read(pcp)

#  define this_cpu_read_2(pcp)	_this_cpu_generic_read(pcp)

#  define this_cpu_read_4(pcp)	_this_cpu_generic_read(pcp)

#  define this_cpu_read_8(pcp)	_this_cpu_generic_read(pcp)

# define this_cpu_read(pcp)	__pcpu_size_call_return(this_cpu_read_, (pcp))

#define _this_cpu_generic_to_op(pcp, val, op)				\
do {									\
	unsigned long flags;						\
	raw_local_irq_save(flags);					\
	*__this_cpu_ptr(&(pcp)) op val;					\
	raw_local_irq_restore(flags);					\
} while (0)

#  define this_cpu_add_1(pcp, val)	_this_cpu_generic_to_op((pcp), (val), +=)

#  define this_cpu_add_2(pcp, val)	_this_cpu_generic_to_op((pcp), (val), +=)

#  define this_cpu_add_4(pcp, val)	_this_cpu_generic_to_op((pcp), (val), +=)

#  define this_cpu_add_8(pcp, val)	_this_cpu_generic_to_op((pcp), (val), +=)

# define this_cpu_add(pcp, val)		__pcpu_size_call(this_cpu_add_, (pcp), (val))

# define this_cpu_inc(pcp)		this_cpu_add((pcp), 1)

#define __this_cpu_generic_to_op(pcp, val, op)				\
do {									\
	*__this_cpu_ptr(&(pcp)) op val;					\
} while (0)

#  define __this_cpu_add_1(pcp, val)	__this_cpu_generic_to_op((pcp), (val), +=)

#  define __this_cpu_add_2(pcp, val)	__this_cpu_generic_to_op((pcp), (val), +=)

#  define __this_cpu_add_4(pcp, val)	__this_cpu_generic_to_op((pcp), (val), +=)

#  define __this_cpu_add_8(pcp, val)	__this_cpu_generic_to_op((pcp), (val), +=)

# define __this_cpu_add(pcp, val)	__pcpu_size_call(__this_cpu_add_, (pcp), (val))

# define __this_cpu_inc(pcp)		__this_cpu_add((pcp), 1)

#endif /* ! __LINUX_PERCPU_H__ */
