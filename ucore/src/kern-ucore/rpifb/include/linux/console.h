#ifndef __LINUX_CONSOLE_H__
#define __LINUX_CONSOLE_H__

#include <linux/types.h>

struct module;
struct tty_struct;

extern int console_trylock(void);
extern void console_unlock(void);

#endif /* ! __LINUX_CONSOLE_H__ */
