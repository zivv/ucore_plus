#ifndef __LINUX_SHRINKER_H__
#define __LINUX_SHRINKER_H__

struct shrink_control {
	gfp_t gfp_mask;

	/* How many slab objects shrinker() should scan and try to reclaim */
	unsigned long nr_to_scan;
};

struct shrinker {
	int (*shrink)(struct shrinker *, struct shrink_control *sc);
	int seeks;	/* seeks to recreate an obj */
	long batch;	/* reclaim batch size, 0 = default */

	/* These are for internal use */
	struct list_head list;
	atomic_long_t nr_in_batch; /* objs pending delete */
};

#endif /* ! __LINUX_SHRINKER_H__ */
