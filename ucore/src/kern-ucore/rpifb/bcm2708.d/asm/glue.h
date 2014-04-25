#ifndef __ASM_GLUE_H__
#define __ASM_GLUE_H__

#define ____glue(name,fn)	name##fn

#define __glue(name,fn)		____glue(name,fn)

#endif /* ! __ASM_GLUE_H__ */
