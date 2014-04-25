#ifndef __LINUX_PM_WAKEUP_H__
#define __LINUX_PM_WAKEUP_H__

#include <linux/types.h>

struct wakeup_source {
	const char 		*name;
	struct list_head	entry;
	spinlock_t		lock;
	struct timer_list	timer;
	unsigned long		timer_expires;
	ktime_t total_time;
	ktime_t max_time;
	ktime_t last_time;
	ktime_t start_prevent_time;
	ktime_t prevent_sleep_time;
	unsigned long		event_count;
	unsigned long		active_count;
	unsigned long		relax_count;
	unsigned long		expire_count;
	unsigned long		wakeup_count;
	bool			active:1;
	bool			autosleep_enabled:1;
};

extern void wakeup_source_prepare(struct wakeup_source *ws, const char *name);

extern void wakeup_source_drop(struct wakeup_source *ws);

extern void wakeup_source_add(struct wakeup_source *ws);
extern void wakeup_source_remove(struct wakeup_source *ws);

#endif /* ! __LINUX_PM_WAKEUP_H__ */
