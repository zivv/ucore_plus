#ifndef __LINUX_JIFFIES_H__
#define __LINUX_JIFFIES_H__

#include <linux/math64.h>
#include <linux/kernel.h>
#include <linux/types.h>
#include <linux/time.h>
#include <linux/timex.h>
#include <asm/param.h>			/* for HZ */

# define SHIFT_HZ	7

#define TICK_NSEC ((NSEC_PER_SEC+HZ/2)/HZ)

#define __jiffy_data  __attribute__((section(".data")))

#define SEC_JIFFIE_SC (31 - SHIFT_HZ)

#undef SEC_JIFFIE_SC

extern clock_t jiffies_to_clock_t(unsigned long x);

#endif /* ! __LINUX_JIFFIES_H__ */
