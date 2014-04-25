#ifndef __MACH_DMA_H__
#define __MACH_DMA_H__

#define BCM2708_DMA_INT		(1 << 2)

#define BCM2708_DMA_INT_EN	(1 << 0)
#define BCM2708_DMA_TDMODE	(1 << 1)

#define BCM2708_DMA_D_INC	(1 << 4)
#define BCM2708_DMA_D_WIDTH	(1 << 5)

#define BCM2708_DMA_S_INC	(1 << 8)
#define BCM2708_DMA_S_WIDTH	(1 << 9)

#define	BCM2708_DMA_BURST(x)	(((x)&0xf) << 12)

#define BCM2708_DMA_CS		0x00 /* Control and Status */

struct bcm2708_dma_cb {
	unsigned long info;
	unsigned long src;
	unsigned long dst;
	unsigned long length;
	unsigned long stride;
	unsigned long next;
	unsigned long pad[2];
};
struct scatterlist;

extern void bcm_dma_start(void __iomem *dma_chan_base,
			  dma_addr_t control_block);
extern void bcm_dma_wait_idle(void __iomem *dma_chan_base);
extern bool bcm_dma_is_busy(void __iomem *dma_chan_base);

#define BCM_DMA_FEATURE_BULK_ORD 1

#define BCM_DMA_FEATURE_BULK	 (1<<BCM_DMA_FEATURE_BULK_ORD)

extern int bcm_dma_chan_alloc(unsigned preferred_feature_set,
			      void __iomem **out_dma_base, int *out_dma_irq);
extern int bcm_dma_chan_free(int channel);

#endif /* ! __MACH_DMA_H__ */
