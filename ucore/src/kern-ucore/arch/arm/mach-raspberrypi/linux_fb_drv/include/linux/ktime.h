#ifndef __LINUX_KTIME_H__
#define __LINUX_KTIME_H__

#include <linux/time.h>
#include <linux/jiffies.h>

union ktime {
	s64	tv64;
#if BITS_PER_LONG != 64 && !defined(CONFIG_KTIME_SCALAR)
	struct {
# ifdef __BIG_ENDIAN
	s32	sec, nsec;
# else
	s32	nsec, sec;
# endif
	} tv;
#endif
};

typedef union ktime ktime_t;		/* Kill this */

static inline ktime_t ktime_set(const long secs, const unsigned long nsecs)
{
#if (BITS_PER_LONG == 64)
	if (unlikely(secs >= KTIME_SEC_MAX))
		return (ktime_t){ .tv64 = KTIME_MAX };
#endif
	return (ktime_t) { .tv64 = (s64)secs * NSEC_PER_SEC + (s64)nsecs };
}

#define ktime_sub(lhs, rhs) \
		({ (ktime_t){ .tv64 = (lhs).tv64 - (rhs).tv64 }; })

#define ktime_add_ns(kt, nsval) \
		({ (ktime_t){ .tv64 = (kt).tv64 + (nsval) }; })

#define ktime_sub_ns(kt, nsval) \
		({ (ktime_t){ .tv64 = (kt).tv64 - (nsval) }; })

#define ktime_to_timespec(kt)		ns_to_timespec((kt).tv64)

#define ktime_to_timeval(kt)		ns_to_timeval((kt).tv64)

#define ktime_to_ns(kt)			((kt).tv64)

static inline s64 ktime_to_us(const ktime_t kt)
{
	struct timeval tv = ktime_to_timeval(kt);
	return (s64) tv.tv_sec * USEC_PER_SEC + tv.tv_usec;
}

extern ktime_t ktime_add_safe(const ktime_t lhs, const ktime_t rhs);

static inline ktime_t ns_to_ktime(u64 ns)
{
	static const ktime_t ktime_zero = { .tv64 = 0 };
	return ktime_add_ns(ktime_zero, ns);
}

#endif /* ! __LINUX_KTIME_H__ */
