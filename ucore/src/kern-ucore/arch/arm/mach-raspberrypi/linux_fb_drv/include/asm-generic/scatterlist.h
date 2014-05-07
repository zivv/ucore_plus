#ifndef __ASM_GENERIC_SCATTERLIST_H__
#define __ASM_GENERIC_SCATTERLIST_H__

#include <linux/types.h>

struct scatterlist {
#ifdef CONFIG_DEBUG_SG
	unsigned long	sg_magic;
#endif
	unsigned long	page_link;
	unsigned int	offset;
	unsigned int	length;
	dma_addr_t	dma_address;
#ifdef CONFIG_NEED_SG_DMA_LENGTH
	unsigned int	dma_length;
#endif
};

#define sg_dma_address(sg)	((sg)->dma_address)

#endif /* ! __ASM_GENERIC_SCATTERLIST_H__ */
