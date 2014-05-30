#ifndef __ASM_MMU_H__
#define __ASM_MMU_H__

typedef struct {
#ifdef CONFIG_CPU_HAS_ASID
	atomic64_t	id;
#else
	int		switch_pending;
#endif
	unsigned int	vmalloc_seq;
	unsigned long	sigpage;
} mm_context_t;

#endif /* ! __ASM_MMU_H__ */