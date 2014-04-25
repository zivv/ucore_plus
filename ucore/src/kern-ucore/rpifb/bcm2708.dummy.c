#include <asm/dma-mapping.h>
#include <asm/io.h>
#include <asm/string.h>
#include <mach/dma.h>
#include <mach/vcio.h>
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

#define DDE_WEAK __attribute__((weak))

#define dde_dummy_printf(...)
#define dde_printf(...) kprintf(__VA_ARGS__)

DDE_WEAK void * __arm_ioremap(unsigned long a, size_t b, unsigned int c) {
	dde_printf("__arm_ioremap not implemented\n");
	return 0;
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

#include <pmm.h>
#include <vmm.h>

void *ucore_kva_alloc_pages(size_t n, unsigned int flags)
{
	struct Page *pages = alloc_pages(n);
	if (!pages)
		return NULL;
	if (flags & UCORE_KAP_IO) {
		int i;
		for (i = 0; i < n; i++)
			SetPageIO(&pages[i]);
	}
	return page2kva(pages);
}

void *arm_dma_alloc(struct device *dev, size_t size, dma_addr_t *handle,
		    gfp_t gfp, struct dma_attrs *attrs)
{
    printk(KERN_ALERT "dma_alloc_writecombine size %08x\n", size);
	void *cpuaddr =
	    ucore_kva_alloc_pages((size + PAGE_SIZE - 1) / PAGE_SIZE,
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

DDE_WEAK int bcm_dma_chan_alloc(unsigned int a, void ** b, int * c) {
	dde_printf("bcm_dma_chan_alloc not implemented\n");
	return 0;
}

DDE_WEAK int bcm_dma_chan_free(int a) {
	dde_printf("bcm_dma_chan_free not implemented\n");
	return 0;
}

DDE_WEAK bool bcm_dma_is_busy(void * a) {
	dde_printf("bcm_dma_is_busy not implemented\n");
	return 0;
}

DDE_WEAK void bcm_dma_start(void * a, dma_addr_t b) {
	dde_printf("bcm_dma_start not implemented\n");
}

DDE_WEAK void bcm_dma_wait_idle(void * a) {
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

DDE_WEAK void free_irq(unsigned int a, void * b) {
	dde_printf("free_irq not implemented\n");
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

DDE_WEAK int request_threaded_irq(unsigned int a, irq_handler_t b, irq_handler_t c, unsigned long d, const char * e, void * f) {
	dde_printf("request_threaded_irq not implemented\n");
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

