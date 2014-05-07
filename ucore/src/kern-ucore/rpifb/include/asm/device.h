#ifndef __ASM_DEVICE_H__
#define __ASM_DEVICE_H__

struct dev_archdata {
	struct dma_map_ops	*dma_ops;
#ifdef CONFIG_DMABOUNCE
	struct dmabounce_device_info *dmabounce;
#endif
#ifdef CONFIG_IOMMU_API
	void *iommu; /* private IOMMU data */
#endif
#ifdef CONFIG_ARM_DMA_USE_IOMMU
	struct dma_iommu_mapping	*mapping;
#endif
};

struct pdev_archdata {
#ifdef CONFIG_ARCH_OMAP
	struct omap_device *od;
#endif
};

#endif /* ! __ASM_DEVICE_H__ */
