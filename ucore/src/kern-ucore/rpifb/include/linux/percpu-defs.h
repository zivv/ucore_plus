#ifndef __LINUX_PERCPU_DEFS_H__
#define __LINUX_PERCPU_DEFS_H__

#define __PCPU_ATTRS(sec)						\
	__percpu __attribute__((section(PER_CPU_BASE_SECTION sec)))	\
	PER_CPU_ATTRIBUTES

#define __verify_pcpu_ptr(ptr)	do {					\
	const void __percpu *__vpp_verify = (typeof(ptr))NULL;		\
	(void)__vpp_verify;						\
} while (0)

#define DECLARE_PER_CPU_SECTION(type, name, sec)			\
	extern __PCPU_ATTRS(sec) __typeof__(type) name

#define DECLARE_PER_CPU(type, name)					\
	DECLARE_PER_CPU_SECTION(type, name, "")

#endif /* ! __LINUX_PERCPU_DEFS_H__ */
