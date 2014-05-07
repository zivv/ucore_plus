#ifndef __ASM_COMPILER_H__
#define __ASM_COMPILER_H__

#define __asmeq(x, y)  ".ifnc " x "," y " ; .err ; .endif\n\t"

#endif /* ! __ASM_COMPILER_H__ */
