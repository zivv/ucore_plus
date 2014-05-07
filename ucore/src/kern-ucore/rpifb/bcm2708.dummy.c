//mach-bcm2708
#include <asm/dma-mapping.h>
#include <asm/io.h>
#include <asm/string.h>
#include <asm/barrier.h>
#include <mach/dma.h>
#include <mach/vcio.h>
#include <mach/irqs.h>
#include <mach/platform.h>

//generic
#include <linux/console.h>
#include <linux/debugfs.h>
#include <linux/device.h>
#include <linux/fb.h>
#include <linux/interrupt.h>
#include <linux/moduleparam.h>
#include <linux/platform_device.h>
#include <linux/printk.h>
#include <linux/sched.h>
#include <linux/slab.h>
#include <linux/slub_def.h>
#include <linux/string.h>
#include <linux/wait.h>
#include <linux/sizes.h>

#include "dde.h" 

#define DDE_WEAK __attribute__((weak))

#define dde_dummy_printf(...)
#define dde_printf(...) kprintf(__VA_ARGS__)

DDE_WEAK void __iomem *__arm_ioremap(unsigned long phys_addr, size_t size,
			    unsigned int mtype)
{
	printk(KERN_INFO "ioremap %08x %08x \n", phys_addr, size);
	return __ucore_ioremap(phys_addr, size, mtype);
}


DDE_WEAK void __arm_iounmap(volatile void * a) {
	dde_printf("__arm_iounmap not implemented\n");
}

DDE_WEAK void __init_waitqueue_head(wait_queue_head_t * a, const char * b, struct lock_class_key * c) {
	dde_printf("__init_waitqueue_head not implemented\n");
}

DDE_WEAK void * __kmalloc(size_t a, gfp_t b) {
	dde_printf("__kmalloc not implemented\n");
	return 0;
}

DDE_WEAK void __memzero(void * a, __kernel_size_t b) {
	dde_printf("__memzero not implemented\n");
}

DDE_WEAK void __wake_up(wait_queue_head_t * a, unsigned int b, int c, void * d) {
	dde_printf("__wake_up not implemented\n");
}

void *arm_dma_alloc(struct device *dev, size_t size, dma_addr_t *handle,
		    gfp_t gfp, struct dma_attrs *attrs)
{
    printk("dma_alloc_writecombine size %08x\n", size);
	void *cpuaddr =
	    dde_kva_alloc_pages((size + PAGE_SIZE - 1) / PAGE_SIZE,
				  UCORE_KAP_IO);
	*handle = (dma_addr_t)__pfn_to_bus(cpuaddr);
	return cpuaddr;

	dde_printf("arm_dma_alloc not implemented\n");
}

struct dma_map_ops arm_dma_ops = {
    .alloc = arm_dma_alloc,
};

DDE_WEAK int autoremove_wake_function(wait_queue_t * a, unsigned int b, int c, void * d) {
	dde_printf("autoremove_wake_function not implemented\n");
	return 0;
}

static unsigned char bcm_dma_irqs[] = {
	IRQ_DMA0,
	IRQ_DMA1,
	IRQ_DMA2,
	IRQ_DMA3,
	IRQ_DMA4,
	IRQ_DMA5,
	IRQ_DMA6,
	IRQ_DMA7,
	IRQ_DMA8,
	IRQ_DMA9,
	IRQ_DMA10,
	IRQ_DMA11,
	IRQ_DMA12
};


#define BCM2708_DMA_CHAN(n)	((n)<<8) /* base address */
#define BCM2708_DMA_CHANIO(dma_base, n) \
   ((void __iomem *)((char *)(dma_base)+BCM2708_DMA_CHAN(n)))

DDE_WEAK int bcm_dma_chan_alloc(unsigned int a, void __iomem **out_dma_base, 
                                int * out_dma_irq) 
{
    int rc = 0;
    resource_size_t DMA_SIZE = SZ_4K;
    void __iomem *dma_base = __arm_ioremap(DMA_BASE, DMA_SIZE, 0);
    *out_dma_base = BCM2708_DMA_CHANIO(dma_base, rc);
    *out_dma_irq = bcm_dma_irqs[rc];
    return rc;

	dde_printf("bcm_dma_chan_alloc not implemented\n");
	return 0;
}

DDE_WEAK int bcm_dma_chan_free(int a) {
	dde_printf("bcm_dma_chan_free not implemented\n");
	return 0;
}

DDE_WEAK bool bcm_dma_is_busy(void __iomem *dma_chan_base) {
	dsb();

	return readl(dma_chan_base + BCM2708_DMA_CS) & BCM2708_DMA_ACTIVE;

	dde_printf("bcm_dma_is_busy not implemented\n");
	return 0;
}

DDE_WEAK void bcm_dma_start(void __iomem *dma_chan_base, 
        dma_addr_t control_block)
{
	dsb();	/* ARM data synchronization (push) operation */

	writel(control_block,	     dma_chan_base + BCM2708_DMA_ADDR);
	writel(BCM2708_DMA_ACTIVE,   dma_chan_base + BCM2708_DMA_CS);

    return;

	dde_printf("bcm_dma_start not implemented\n");
}

DDE_WEAK void bcm_dma_wait_idle(void __iomem * dma_chan_base) {
    dsb();

  /* ugly busy wait only option for now */
    while (readl(dma_chan_base + BCM2708_DMA_CS) & BCM2708_DMA_ACTIVE)
        cpu_relax();

    return;

	dde_printf("bcm_dma_wait_idle not implemented\n");
}

DDE_WEAK int bcm_mailbox_read(unsigned int a, uint32_t * b) {
	dde_printf("bcm_mailbox_read not implemented\n");
	return 0;
}

DDE_WEAK int bcm_mailbox_write(unsigned int a, uint32_t b) {
	dde_printf("bcm_mailbox_write not implemented\n");
	return 0;
}

DDE_WEAK void cfb_copyarea(struct fb_info * a, const struct fb_copyarea * b) {
	dde_printf("cfb_copyarea not implemented\n");
}

DDE_WEAK void cfb_fillrect(struct fb_info * a, const struct fb_fillrect * b) {
	dde_printf("cfb_fillrect not implemented\n");
}

DDE_WEAK void cfb_imageblit(struct fb_info * a, const struct fb_image * b) {
	dde_printf("cfb_imageblit not implemented\n");
}

DDE_WEAK int console_trylock() {
	dde_printf("console_trylock not implemented\n");
	return 0;
}

DDE_WEAK void console_unlock() {
	dde_printf("console_unlock not implemented\n");
}

DDE_WEAK struct dentry * debugfs_create_dir(const char * a, struct dentry * b) {
	dde_printf("debugfs_create_dir not implemented\n");
	return 0;
}

DDE_WEAK struct dentry * debugfs_create_regset32(const char * a, umode_t b, struct dentry * c, struct debugfs_regset32 * d) {
	dde_printf("debugfs_create_regset32 not implemented\n");
	return 0;
}

DDE_WEAK void debugfs_remove_recursive(struct dentry * a) {
	dde_printf("debugfs_remove_recursive not implemented\n");
}

DDE_WEAK int dev_err(const struct device * a, const char * b, ...) {
	dde_printf("dev_err not implemented\n");
	return 0;
}

DDE_WEAK void * dev_get_drvdata(const struct device * a) {
	dde_printf("dev_get_drvdata not implemented\n");
	return 0;
}

DDE_WEAK int dev_set_drvdata(struct device * a, void * b) {
	dde_printf("dev_set_drvdata not implemented\n");
	return 0;
}

DDE_WEAK int fb_set_var(struct fb_info * a, struct fb_var_screeninfo * b) {
	dde_printf("fb_set_var not implemented\n");
	return 0;
}

DDE_WEAK void finish_wait(wait_queue_head_t * a, wait_queue_t * b) {
	dde_printf("finish_wait not implemented\n");
}

DDE_WEAK void free_irq(unsigned int irq, void * dev_id) {
  irq_clear(irq);
	//dde_printf("free_irq not implemented\n");
}

DDE_WEAK void kfree(const void * a) {
	dde_printf("kfree not implemented\n");
}

struct kernel_param_ops param_ops_int;

DDE_WEAK int platform_driver_register(struct platform_driver * a) {
    bcm2708_fb_probe(NULL);
	dde_printf("platform_driver_register not implemented\n");
	return 0;
}

DDE_WEAK void platform_driver_unregister(struct platform_driver * a) {
	dde_printf("platform_driver_unregister not implemented\n");
}

DDE_WEAK void prepare_to_wait(wait_queue_head_t * a, wait_queue_t * b, int c) {
	dde_printf("prepare_to_wait not implemented\n");
}

DDE_WEAK int printk(const char * a, ...) {
	dde_printf("printk not implemented\n");
	return 0;
}

DDE_WEAK int register_framebuffer(struct fb_info * a) {
	dde_printf("register_framebuffer not implemented\n");
	return 0;
}

DDE_WEAK int request_threaded_irq(unsigned int irq, irq_handler_t handler,
    irq_handler_t thread_fn, unsigned long flags, const char * name, void * dev) {
  register_irq(irq, handler, NULL);
	//dde_printf("request_threaded_irq not implemented\n");
	return 0;
}

DDE_WEAK void schedule() {
	dde_printf("schedule not implemented\n");
}

DDE_WEAK char * strncpy(char * a, const char * b, __kernel_size_t c) {
	dde_printf("strncpy not implemented\n");
	return 0;
}

DDE_WEAK int unregister_framebuffer(struct fb_info * a) {
	dde_printf("unregister_framebuffer not implemented\n");
	return 0;
}

