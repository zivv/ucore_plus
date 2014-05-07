#ifndef __ASM_IO_H__
#define __ASM_IO_H__

#include <linux/types.h>
#include <asm/byteorder.h>
#include <asm/memory.h>
#include <asm-generic/pci_iomap.h>

static inline void __raw_writel(u32 val, volatile void __iomem *addr)
{
	asm volatile("str %1, %0"
		     : "+Qo" (*(volatile u32 __force *)addr)
		     : "r" (val));
}
static inline u32 __raw_readl(const volatile void __iomem *addr)
{
	u32 val;
	asm volatile("ldr %1, %0"
		     : "+Qo" (*(volatile u32 __force *)addr),
		       "=r" (val));
	return val;
}


#define MT_DEVICE_WC		3

extern void __iomem *__arm_ioremap(unsigned long, size_t, unsigned int);

extern void __arm_iounmap(volatile void __iomem *addr);

#include <asm/barrier.h>

#define __iowmb()		wmb()
#define __iormb()		rmb()

#include <mach/io.h>

#define writel_relaxed(v,c)	__raw_writel((__force u32) cpu_to_le32(v),c)
#define readl_relaxed(c) ({ u32 __r = le32_to_cpu((__force __le32) \
					__raw_readl(c)); __r; })

#define writel(v,c)		({ __iowmb(); writel_relaxed(v,c); })
#define readl(c)		({ u32 __v = readl_relaxed(c); __iormb(); __v; })

#define ioremap_wc(cookie,size)		__arm_ioremap((cookie), (size), MT_DEVICE_WC)
#define iounmap				__arm_iounmap

#endif /* ! __ASM_IO_H__ */
