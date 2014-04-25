#ifndef __LINUX_MM_H__
#define __LINUX_MM_H__

#define _LINUX_MM_H

#include <linux/errno.h>

#include <linux/gfp.h>
#include <linux/bug.h>
#include <linux/list.h>
#include <linux/mmzone.h>
#include <linux/rbtree.h>
#include <linux/atomic.h>
#include <linux/debug_locks.h>
#include <linux/mm_types.h>
#include <linux/range.h>
#include <linux/pfn.h>
#include <linux/bit_spinlock.h>
#include <linux/shrinker.h>

struct anon_vma;

struct file_ra_state;
struct user_struct;
struct writeback_control;

extern unsigned long totalram_pages;
extern void * high_memory;

#include <asm/page.h>
#include <asm/pgtable.h>
#include <asm/processor.h>

#define nth_page(page,n) pfn_to_page(page_to_pfn((page)) + (n))

#define PAGE_ALIGN(addr) ALIGN(addr, PAGE_SIZE)

#define VM_NONE		0x00000000

#define VM_WRITE	0x00000002

#define VM_GROWSDOWN	0x00000100	/* general info on the segment */

# define VM_GROWSUP	VM_NONE

struct vm_fault {
	unsigned int flags;		/* FAULT_FLAG_xxx flags */
	pgoff_t pgoff;			/* Logical page offset based on vma */
	void __user *virtual_address;	/* Faulting virtual address */

	struct page *page;		/* ->fault handlers should return a
					 * page here, unless VM_FAULT_NOPAGE
					 * is set (which is also implied by
					 * VM_FAULT_ERROR).
					 */
};

struct vm_operations_struct {
	void (*open)(struct vm_area_struct * area);
	void (*close)(struct vm_area_struct * area);
	int (*fault)(struct vm_area_struct *vma, struct vm_fault *vmf);

	/* notification that a previously read-only page is about to become
	 * writable, if an error is returned it will cause a SIGBUS */
	int (*page_mkwrite)(struct vm_area_struct *vma, struct vm_fault *vmf);

	/* called by access_process_vm when get_user_pages() fails, typically
	 * for use by special VMAs that can switch between memory and hardware
	 */
	int (*access)(struct vm_area_struct *vma, unsigned long addr,
		      void *buf, int len, int write);
#ifdef CONFIG_NUMA
	/*
	 * set_policy() op must add a reference to any non-NULL @new mempolicy
	 * to hold the policy upon return.  Caller should pass NULL @new to
	 * remove a policy and fall back to surrounding context--i.e. do not
	 * install a MPOL_DEFAULT policy, nor the task or system default
	 * mempolicy.
	 */
	int (*set_policy)(struct vm_area_struct *vma, struct mempolicy *new);

	/*
	 * get_policy() op must add reference [mpol_get()] to any policy at
	 * (vma,addr) marked as MPOL_SHARED.  The shared policy infrastructure
	 * in mm/mempolicy.c will do this automatically.
	 * get_policy() must NOT add a ref if the policy at (vma,addr) is not
	 * marked as MPOL_SHARED. vma policies are protected by the mmap_sem.
	 * If no [shared/vma] mempolicy exists at the addr, get_policy() op
	 * must return NULL--i.e., do not "fallback" to task or system default
	 * policy.
	 */
	struct mempolicy *(*get_policy)(struct vm_area_struct *vma,
					unsigned long addr);
	int (*migrate)(struct vm_area_struct *vma, const nodemask_t *from,
		const nodemask_t *to, unsigned long flags);
#endif
	/* called by sys_remap_file_pages() to populate non-linear mapping */
	int (*remap_pages)(struct vm_area_struct *vma, unsigned long addr,
			   unsigned long size, pgoff_t pgoff);
};

struct inode;

#define page_private(page)		((page)->private)

#include <linux/page-flags.h>
#include <linux/huge_mm.h>

static inline unsigned long compound_lock_irqsave(struct page *page)
{
	unsigned long uninitialized_var(flags);
#ifdef CONFIG_TRANSPARENT_HUGEPAGE
	local_irq_save(flags);
	compound_lock(page);
#endif
	return flags;
}

static inline void compound_unlock_irqrestore(struct page *page,
					      unsigned long flags)
{
#ifdef CONFIG_TRANSPARENT_HUGEPAGE
	compound_unlock(page);
	local_irq_restore(flags);
#endif
}

static inline struct page *compound_head(struct page *page)
{
	if (unlikely(PageTail(page)))
		return page->first_page;
	return page;
}

static inline int page_mapcount(struct page *page)
{
	return atomic_read(&(page)->_mapcount) + 1;
}

extern bool __get_page_tail(struct page *page);

static inline void init_page_count(struct page *page)
{
	atomic_set(&page->_count, 1);
}

#define PAGE_BUDDY_MAPCOUNT_VALUE (-128)

static inline int PageBuddy(struct page *page)
{
	return atomic_read(&page->_mapcount) == PAGE_BUDDY_MAPCOUNT_VALUE;
}

static inline int compound_order(struct page *page)
{
	if (!PageHead(page))
		return 0;
	return (unsigned long)page[1].lru.prev;
}

#define SECTIONS_PGOFF		((sizeof(unsigned long)*8) - SECTIONS_WIDTH)
#define NODES_PGOFF		(SECTIONS_PGOFF - NODES_WIDTH)
#define ZONES_PGOFF		(NODES_PGOFF - ZONES_WIDTH)

#define NODES_PGSHIFT		(NODES_PGOFF * (NODES_WIDTH != 0))
#define ZONES_PGSHIFT		(ZONES_PGOFF * (ZONES_WIDTH != 0))

#define ZONEID_SHIFT		(NODES_SHIFT + ZONES_SHIFT)
#define ZONEID_PGOFF		((NODES_PGOFF < ZONES_PGOFF)? \
						NODES_PGOFF : ZONES_PGOFF)

#define ZONEID_PGSHIFT		(ZONEID_PGOFF * (ZONEID_SHIFT != 0))

#define ZONES_MASK		((1UL << ZONES_WIDTH) - 1)
#define NODES_MASK		((1UL << NODES_WIDTH) - 1)

#define ZONEID_MASK		((1UL << ZONEID_SHIFT) - 1)

static inline enum zone_type page_zonenum(const struct page *page)
{
	return (page->flags >> ZONES_PGSHIFT) & ZONES_MASK;
}

static inline int page_to_nid(const struct page *page)
{
	return (page->flags >> NODES_PGSHIFT) & NODES_MASK;
}

static inline struct zone *page_zone(const struct page *page)
{
	return &NODE_DATA(page_to_nid(page))->node_zones[page_zonenum(page)];
}

static inline void set_page_zone(struct page *page, enum zone_type zone)
{
	page->flags &= ~(ZONES_MASK << ZONES_PGSHIFT);
	page->flags |= (zone & ZONES_MASK) << ZONES_PGSHIFT;
}

static inline void set_page_node(struct page *page, unsigned long node)
{
	page->flags &= ~(NODES_MASK << NODES_PGSHIFT);
	page->flags |= (node & NODES_MASK) << NODES_PGSHIFT;
}

#include <linux/vmstat.h>

static __always_inline void *lowmem_page_address(const struct page *page)
{
	return __va(PFN_PHYS(page_to_pfn(page)));
}

#define page_address(page) lowmem_page_address(page)

#define PAGE_MAPPING_ANON	1
#define PAGE_MAPPING_KSM	2
#define PAGE_MAPPING_FLAGS	(PAGE_MAPPING_ANON | PAGE_MAPPING_KSM)

extern struct address_space *__page_file_mapping(struct page *);

extern pgoff_t __page_file_index(struct page *page);

#define offset_in_page(p)	((unsigned long)(p) & ~PAGE_MASK)

void unmap_mapping_range(struct address_space *mapping,
		loff_t const holebegin, loff_t const holelen, int even_cows);

static inline int vma_growsdown(struct vm_area_struct *vma, unsigned long addr)
{
	return vma && (vma->vm_end == addr) && (vma->vm_flags & VM_GROWSDOWN);
}

static inline int vma_growsup(struct vm_area_struct *vma, unsigned long addr)
{
	return vma && (vma->vm_start == addr) && (vma->vm_flags & VM_GROWSUP);
}

static inline unsigned long get_mm_counter(struct mm_struct *mm, int member)
{
	long val = atomic_long_read(&mm->rss_stat.count[member]);

#ifdef SPLIT_RSS_COUNTING
	/*
	 * counter is updated in asynchronous manner and may go to minus.
	 * But it's never be expected number for users.
	 */
	if (val < 0)
		val = 0;
#endif
	return (unsigned long)val;
}

static inline unsigned long get_mm_rss(struct mm_struct *mm)
{
	return get_mm_counter(mm, MM_FILEPAGES) +
		get_mm_counter(mm, MM_ANONPAGES);
}

static inline unsigned long get_mm_hiwater_rss(struct mm_struct *mm)
{
	return max(mm->hiwater_rss, get_mm_rss(mm));
}

extern pte_t *__get_locked_pte(struct mm_struct *mm, unsigned long addr,
			       spinlock_t **ptl);

static inline int __pud_alloc(struct mm_struct *mm, pgd_t *pgd,
						unsigned long address)
{
	return 0;
}

int __pmd_alloc(struct mm_struct *mm, pud_t *pud, unsigned long address);

#define pte_lock_init(page)	do {} while (0)
#define pte_lock_deinit(page)	do {} while (0)

extern unsigned long free_reserved_area(unsigned long start, unsigned long end,
					int poison, char *s);

static inline void adjust_managed_page_count(struct page *page, long count)
{
	totalram_pages += count;
}

static inline void __free_reserved_page(struct page *page)
{
	ClearPageReserved(page);
	init_page_count(page);
	__free_page(page);
}

extern int __mm_populate(unsigned long addr, unsigned long len,
			 int ignore_errors);

struct vm_unmapped_area_info {
#define VM_UNMAPPED_AREA_TOPDOWN 1
	unsigned long flags;
	unsigned long length;
	unsigned long low_limit;
	unsigned long high_limit;
	unsigned long align_mask;
	unsigned long align_offset;
};

extern unsigned long unmapped_area(struct vm_unmapped_area_info *info);
extern unsigned long unmapped_area_topdown(struct vm_unmapped_area_info *info);

extern struct vm_area_struct * find_vma(struct mm_struct * mm, unsigned long addr);

struct page *follow_page_mask(struct vm_area_struct *vma,
			      unsigned long address, unsigned int foll_flags,
			      unsigned int *page_mask);

#endif /* ! __LINUX_MM_H__ */
