#ifndef __LINUX_TYPECHECK_H__
#define __LINUX_TYPECHECK_H__

#define typecheck(type,x) \
({	type __dummy; \
	typeof(x) __dummy2; \
	(void)(&__dummy == &__dummy2); \
	1; \
})

#endif /* ! __LINUX_TYPECHECK_H__ */
