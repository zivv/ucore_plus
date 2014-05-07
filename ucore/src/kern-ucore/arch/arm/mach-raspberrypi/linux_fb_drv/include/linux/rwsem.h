#ifndef __LINUX_RWSEM_H__
#define __LINUX_RWSEM_H__

#define _LINUX_RWSEM_H

#include <linux/linkage.h>

#include <linux/types.h>
#include <linux/kernel.h>
#include <linux/list.h>
#include <linux/spinlock.h>

#include <linux/atomic.h>

struct rw_semaphore;

#include <linux/rwsem-spinlock.h> /* use a generic implementation */

extern void down_read(struct rw_semaphore *sem);

extern void down_write(struct rw_semaphore *sem);

extern void up_read(struct rw_semaphore *sem);

extern void up_write(struct rw_semaphore *sem);

#endif /* ! __LINUX_RWSEM_H__ */
