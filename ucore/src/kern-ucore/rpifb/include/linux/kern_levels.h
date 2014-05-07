#ifndef __LINUX_KERN_LEVELS_H__
#define __LINUX_KERN_LEVELS_H__

#define KERN_SOH	"\001"		/* ASCII Start Of Header */
#define KERN_SOH_ASCII	'\001'

#define KERN_ERR	KERN_SOH "3"	/* error conditions */
#define KERN_WARNING	KERN_SOH "4"	/* warning conditions */

#define KERN_INFO	KERN_SOH "6"	/* informational */

#endif /* ! __LINUX_KERN_LEVELS_H__ */
