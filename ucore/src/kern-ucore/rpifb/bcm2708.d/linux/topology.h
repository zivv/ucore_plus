#ifndef __LINUX_TOPOLOGY_H__
#define __LINUX_TOPOLOGY_H__

#include <linux/cpumask.h>
#include <linux/bitops.h>
#include <linux/mmzone.h>
#include <linux/smp.h>
#include <linux/percpu.h>
#include <asm/topology.h>

static inline int numa_node_id(void)
{
	return cpu_to_node(raw_smp_processor_id());
}

#endif /* ! __LINUX_TOPOLOGY_H__ */
