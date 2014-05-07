#ifndef __LINUX_DEBUGFS_H__
#define __LINUX_DEBUGFS_H__

#include <linux/fs.h>
#include <linux/seq_file.h>

#include <linux/types.h>

struct file_operations;

struct debugfs_reg32 {
	char *name;
	unsigned long offset;
};

struct debugfs_regset32 {
	const struct debugfs_reg32 *regs;
	int nregs;
	void __iomem *base;
};

struct dentry *debugfs_create_dir(const char *name, struct dentry *parent);

void debugfs_remove_recursive(struct dentry *dentry);

struct dentry *debugfs_create_regset32(const char *name, umode_t mode,
				     struct dentry *parent,
				     struct debugfs_regset32 *regset);

#endif /* ! __LINUX_DEBUGFS_H__ */
