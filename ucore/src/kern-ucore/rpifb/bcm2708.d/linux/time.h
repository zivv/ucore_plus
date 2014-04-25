#ifndef __LINUX_TIME_H__
#define __LINUX_TIME_H__

# include <linux/cache.h>
# include <linux/seqlock.h>
# include <linux/math64.h>
#include <uapi/linux/time.h>

#define MSEC_PER_SEC	1000L
#define USEC_PER_MSEC	1000L
#define NSEC_PER_USEC	1000L

#define USEC_PER_SEC	1000000L
#define NSEC_PER_SEC	1000000000L

extern void set_normalized_timespec(struct timespec *ts, time_t sec, s64 nsec);

# define KTIME_SEC_MAX			LONG_MAX

static inline bool timespec_valid(const struct timespec *ts)
{
	/* Dates before 1970 are bogus */
	if (ts->tv_sec < 0)
		return false;
	/* Can't have more nanoseconds then a second */
	if ((unsigned long)ts->tv_nsec >= NSEC_PER_SEC)
		return false;
	return true;
}

extern bool persistent_clock_exist;

extern struct timespec ns_to_timespec(const s64 nsec);

extern struct timeval ns_to_timeval(const s64 nsec);

#endif /* ! __LINUX_TIME_H__ */
