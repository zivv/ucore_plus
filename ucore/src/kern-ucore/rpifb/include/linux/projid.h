#ifndef __LINUX_PROJID_H__
#define __LINUX_PROJID_H__

#include <linux/types.h>

struct user_namespace;
extern struct user_namespace init_user_ns;

typedef __kernel_uid32_t projid_t;

typedef projid_t kprojid_t;

static inline projid_t __kprojid_val(kprojid_t projid)
{
	return projid;
}

#define KPROJIDT_INIT(value) ((kprojid_t) value )

#define INVALID_PROJID KPROJIDT_INIT(-1)
#define OVERFLOW_PROJID 65534

static inline bool projid_eq(kprojid_t left, kprojid_t right)
{
	return __kprojid_val(left) == __kprojid_val(right);
}

static inline kprojid_t make_kprojid(struct user_namespace *from, projid_t projid)
{
	return KPROJIDT_INIT(projid);
}

static inline projid_t from_kprojid(struct user_namespace *to, kprojid_t kprojid)
{
	return __kprojid_val(kprojid);
}

#endif /* ! __LINUX_PROJID_H__ */
