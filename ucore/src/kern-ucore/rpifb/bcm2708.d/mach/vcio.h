#ifndef __MACH_VCIO_H__
#define __MACH_VCIO_H__

#define MBOX_CHAN_FB       1 /* for use by the frame buffer */

extern int /*rc*/ bcm_mailbox_read(unsigned chan, uint32_t *data28);
extern int /*rc*/ bcm_mailbox_write(unsigned chan, uint32_t data28);

#include <linux/ioctl.h>

#endif /* ! __MACH_VCIO_H__ */
