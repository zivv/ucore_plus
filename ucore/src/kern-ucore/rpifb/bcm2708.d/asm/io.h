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

#define MT_DEVICE_WC		3

extern void __iomem *__arm_ioremap(unsigned long, size_t, unsigned int);

extern void __arm_iounmap(volatile void __iomem *addr);

#include <asm/barrier.h>

#define __iowmb()		wmb()

#include <mach/io.h>

#define writel_relaxed(v,c)	__raw_writel((__force u32) cpu_to_le32(v),c)

#define writel(v,c)		({ __iowmb(); writel_relaxed(v,c); })

#define ioremap_wc(cookie,size)		__arm_ioremap((cookie), (size), MT_DEVICE_WC)
#define iounmap				__arm_iounmap

#endif /* ! __ASM_IO_H__ */
