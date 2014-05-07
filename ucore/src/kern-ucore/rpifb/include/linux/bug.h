#ifndef __LINUX_BUG_H__
#define __LINUX_BUG_H__

#include <asm/bug.h>
#include <linux/compiler.h>

#define BUILD_BUG_ON_ZERO(e) (sizeof(struct { int:-!!(e); }))

#define BUILD_BUG_ON_INVALID(e) ((void)(sizeof((__force long)(e))))

#include <asm-generic/bug.h>

#endif /* ! __LINUX_BUG_H__ */
