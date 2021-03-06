#ifndef __UAPI_ASM_FCNTL_H__
#define __UAPI_ASM_FCNTL_H__

#define O_DIRECTORY	 040000	/* must be a directory */
#define O_NOFOLLOW	0100000	/* don't follow links */
#define O_DIRECT	0200000	/* direct disk access hint - currently ignored */
#define O_LARGEFILE	0400000

#include <asm-generic/fcntl.h>

#endif /* ! __UAPI_ASM_FCNTL_H__ */
