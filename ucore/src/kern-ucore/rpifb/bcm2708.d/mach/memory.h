#ifndef __MACH_MEMORY_H__
#define __MACH_MEMORY_H__

#define PLAT_PHYS_OFFSET	UL(0x00000000)
#define VC_ARMMEM_OFFSET	UL(0x00000000)   /* offset in VC of ARM memory */

 #define _REAL_BUS_OFFSET UL(0x40000000)   /* use L2 cache */

#define BUS_OFFSET          (VC_ARMMEM_OFFSET + _REAL_BUS_OFFSET)
#define __virt_to_bus(x)    ((x) + (BUS_OFFSET - PAGE_OFFSET))
#define __bus_to_virt(x)    ((x) - (BUS_OFFSET - PAGE_OFFSET))
#define __pfn_to_bus(x)     (__pfn_to_phys(x) + (BUS_OFFSET - PLAT_PHYS_OFFSET))
#define __bus_to_pfn(x)     __phys_to_pfn((x) - (BUS_OFFSET - PLAT_PHYS_OFFSET))

#endif /* ! __MACH_MEMORY_H__ */
