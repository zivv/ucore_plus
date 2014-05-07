#ifndef __LINUX_PRINTK_H__
#define __LINUX_PRINTK_H__

#include <stdarg.h>
#include <linux/init.h>
#include <linux/kern_levels.h>
#include <linux/linkage.h>

static inline int printk_get_level(const char *buffer)
{
	if (buffer[0] == KERN_SOH_ASCII && buffer[1]) {
		switch (buffer[1]) {
		case '0' ... '7':
		case 'd':	/* KERN_DEFAULT */
			return buffer[1];
		}
	}
	return 0;
}

extern int console_printk[];

#define console_loglevel (console_printk[0])

asmlinkage __printf(1, 2) __cold
int printk(const char *fmt, ...);

extern void dump_stack(void) __cold;

#define pr_fmt(fmt) fmt

#define pr_err(fmt, ...) \
	printk(KERN_ERR pr_fmt(fmt), ##__VA_ARGS__)
#define pr_warning(fmt, ...) \
	printk(KERN_WARNING pr_fmt(fmt), ##__VA_ARGS__)
#define pr_warn pr_warning

#define pr_info(fmt, ...) \
	printk(KERN_INFO pr_fmt(fmt), ##__VA_ARGS__)

extern const struct file_operations kmsg_fops;

#endif /* ! __LINUX_PRINTK_H__ */
