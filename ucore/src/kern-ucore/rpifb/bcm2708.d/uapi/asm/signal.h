#ifndef __UAPI_ASM_SIGNAL_H__
#define __UAPI_ASM_SIGNAL_H__

#include <linux/types.h>

struct siginfo;

#define SIGTRAP		 5

#define SIGKILL		 9

#define SIGSTOP		19

#define SIGRTMIN	32

#define SA_ONSTACK	0x08000000

#include <asm-generic/signal-defs.h>

#endif /* ! __UAPI_ASM_SIGNAL_H__ */
