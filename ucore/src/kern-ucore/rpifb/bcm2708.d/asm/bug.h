#ifndef __ASM_BUG_H__
#define __ASM_BUG_H__

#include <linux/linkage.h>

#define BUG_INSTR_VALUE 0xe7f001f2
#define BUG_INSTR_TYPE ".word "

#define BUG() _BUG(__FILE__, __LINE__, BUG_INSTR_VALUE)
#define _BUG(file, line, value) __BUG(file, line, value)

#define __BUG(__file, __line, __value)				\
do {								\
	asm volatile("1:\t" BUG_INSTR_TYPE #__value "\n"	\
		".pushsection .rodata.str, \"aMS\", %progbits, 1\n" \
		"2:\t.asciz " #__file "\n" 			\
		".popsection\n" 				\
		".pushsection __bug_table,\"a\"\n"		\
		"3:\t.word 1b, 2b\n"				\
		"\t.hword " #__line ", 0\n"			\
		".popsection");					\
	unreachable();						\
} while (0)

#define HAVE_ARCH_BUG

#include <asm-generic/bug.h>

struct siginfo;

struct mm_struct;

#endif /* ! __ASM_BUG_H__ */
