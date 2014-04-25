#ifndef __LINUX_CLK_H__
#define __LINUX_CLK_H__

#include <linux/err.h>
#include <linux/kernel.h>
#include <linux/notifier.h>

struct device;

struct clk;

static inline int clk_prepare(struct clk *clk)
{
	might_sleep();
	return 0;
}

static inline void clk_unprepare(struct clk *clk)
{
	might_sleep();
}

int clk_enable(struct clk *clk);

void clk_disable(struct clk *clk);

struct device_node;

#endif /* ! __LINUX_CLK_H__ */
