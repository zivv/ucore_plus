#ifndef __ASM_GLUE_PROC_H__
#define __ASM_GLUE_PROC_H__

#include <asm/glue.h>

#  define CPU_NAME cpu_v6

#define cpu_proc_init			__glue(CPU_NAME,_proc_init)
#define cpu_proc_fin			__glue(CPU_NAME,_proc_fin)
#define cpu_reset			__glue(CPU_NAME,_reset)
#define cpu_do_idle			__glue(CPU_NAME,_do_idle)
#define cpu_dcache_clean_area		__glue(CPU_NAME,_dcache_clean_area)
#define cpu_do_switch_mm		__glue(CPU_NAME,_switch_mm)
#define cpu_set_pte_ext			__glue(CPU_NAME,_set_pte_ext)

#define cpu_do_suspend			__glue(CPU_NAME,_do_suspend)
#define cpu_do_resume			__glue(CPU_NAME,_do_resume)

#endif /* ! __ASM_GLUE_PROC_H__ */
