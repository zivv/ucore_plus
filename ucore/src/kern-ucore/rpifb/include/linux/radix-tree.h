#ifndef __LINUX_RADIX_TREE_H__
#define __LINUX_RADIX_TREE_H__

#include <linux/preempt.h>
#include <linux/types.h>
#include <linux/bug.h>
#include <linux/kernel.h>
#include <linux/rcupdate.h>

#define RADIX_TREE_INDIRECT_PTR		1

#define RADIX_TREE_EXCEPTIONAL_ENTRY	2

static inline int radix_tree_is_indirect_ptr(void *ptr)
{
	return (int)((unsigned long)ptr & RADIX_TREE_INDIRECT_PTR);
}

struct radix_tree_root {
	unsigned int		height;
	gfp_t			gfp_mask;
	struct radix_tree_node	__rcu *rnode;
};

struct radix_tree_iter {
	unsigned long	index;
	unsigned long	next_index;
	unsigned long	tags;
};

#define RADIX_TREE_ITER_TAGGED		0x0100	/* lookup tagged slots */
#define RADIX_TREE_ITER_CONTIG		0x0200	/* stop at first hole */

static __always_inline unsigned
radix_tree_chunk_size(struct radix_tree_iter *iter)
{
	return iter->next_index - iter->index;
}

#endif /* ! __LINUX_RADIX_TREE_H__ */
