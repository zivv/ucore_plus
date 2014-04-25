#ifndef __LINUX_VMSTAT_H__
#define __LINUX_VMSTAT_H__

#include <linux/types.h>
#include <linux/percpu.h>
#include <linux/mm.h>
#include <linux/mmzone.h>
#include <linux/vm_event_item.h>
#include <linux/atomic.h>

struct vm_event_state {
	unsigned long event[NR_VM_EVENT_ITEMS];
};

DECLARE_PER_CPU(struct vm_event_state, vm_event_states);

extern atomic_long_t vm_stat[NR_VM_ZONE_STAT_ITEMS];

static inline void zone_page_state_add(long x, struct zone *zone,
				 enum zone_stat_item item)
{
	atomic_long_add(x, &zone->vm_stat[item]);
	atomic_long_add(x, &vm_stat[item]);
}

static inline void __mod_zone_page_state(struct zone *zone,
			enum zone_stat_item item, int delta)
{
	zone_page_state_add(delta, zone, item);
}

static inline void __inc_zone_state(struct zone *zone, enum zone_stat_item item)
{
	atomic_long_inc(&zone->vm_stat[item]);
	atomic_long_inc(&vm_stat[item]);
}

static inline void __inc_zone_page_state(struct page *page,
			enum zone_stat_item item)
{
	__inc_zone_state(page_zone(page), item);
}

static inline void __dec_zone_state(struct zone *zone, enum zone_stat_item item)
{
	atomic_long_dec(&zone->vm_stat[item]);
	atomic_long_dec(&vm_stat[item]);
}

static inline void __dec_zone_page_state(struct page *page,
			enum zone_stat_item item)
{
	__dec_zone_state(page_zone(page), item);
}

#define inc_zone_page_state __inc_zone_page_state
#define dec_zone_page_state __dec_zone_page_state

#endif /* ! __LINUX_VMSTAT_H__ */
