#ifndef __ASM_DMA_MAPPING_H__
#define __ASM_DMA_MAPPING_H__

#include <linux/mm_types.h>
#include <linux/scatterlist.h>
#include <linux/dma-attrs.h>
#include <linux/dma-debug.h>

#include <asm-generic/dma-coherent.h>
#include <asm/memory.h>

#define DMA_ERROR_CODE	(~0)
extern struct dma_map_ops arm_dma_ops;

static inline struct dma_map_ops *get_dma_ops(struct device *dev)
{
	if (dev && dev->archdata.dma_ops)
		return dev->archdata.dma_ops;
	return &arm_dma_ops;
}

#include <asm-generic/dma-mapping-common.h>

extern int dma_supported(struct device *dev, u64 mask);

#define dma_alloc_coherent(d, s, h, f) dma_alloc_attrs(d, s, h, f, NULL)

static inline void *dma_alloc_attrs(struct device *dev, size_t size,
				       dma_addr_t *dma_handle, gfp_t flag,
				       struct dma_attrs *attrs)
{
	struct dma_map_ops *ops = get_dma_ops(dev);
	void *cpu_addr;
	BUG_ON(!ops);

	cpu_addr = ops->alloc(dev, size, dma_handle, flag, attrs);
	debug_dma_alloc_coherent(dev, size, *dma_handle, cpu_addr);
	return cpu_addr;
}

#define dma_free_coherent(d, s, c, h) dma_free_attrs(d, s, c, h, NULL)

static inline void dma_free_attrs(struct device *dev, size_t size,
				     void *cpu_addr, dma_addr_t dma_handle,
				     struct dma_attrs *attrs)
{
	struct dma_map_ops *ops = get_dma_ops(dev);
	BUG_ON(!ops);

	debug_dma_free_coherent(dev, size, cpu_addr, dma_handle);
	ops->free(dev, size, cpu_addr, dma_handle, attrs);
}

static inline void *dma_alloc_writecombine(struct device *dev, size_t size,
				       dma_addr_t *dma_handle, gfp_t flag)
{
	DEFINE_DMA_ATTRS(attrs);
	dma_set_attr(DMA_ATTR_WRITE_COMBINE, &attrs);
	return dma_alloc_attrs(dev, size, dma_handle, flag, &attrs);
}

static inline void dma_free_writecombine(struct device *dev, size_t size,
				     void *cpu_addr, dma_addr_t dma_handle)
{
	DEFINE_DMA_ATTRS(attrs);
	dma_set_attr(DMA_ATTR_WRITE_COMBINE, &attrs);
	return dma_free_attrs(dev, size, cpu_addr, dma_handle, &attrs);
}

#endif /* ! __ASM_DMA_MAPPING_H__ */
