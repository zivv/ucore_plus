#ifndef __LINUX_CRED_H__
#define __LINUX_CRED_H__

#include <linux/capability.h>
#include <linux/init.h>
#include <linux/key.h>
#include <linux/selinux.h>
#include <linux/atomic.h>
#include <linux/uidgid.h>

struct user_struct;
struct cred;
struct inode;

#define NGROUPS_SMALL		32

struct group_info {
	atomic_t	usage;
	int		ngroups;
	int		nblocks;
	kgid_t		small_block[NGROUPS_SMALL];
	kgid_t		*blocks[0];
};

struct cred {
	atomic_t	usage;
#ifdef CONFIG_DEBUG_CREDENTIALS
	atomic_t	subscribers;	/* number of processes subscribed */
	void		*put_addr;
	unsigned	magic;
#define CRED_MAGIC	0x43736564
#define CRED_MAGIC_DEAD	0x44656144
#endif
	kuid_t		uid;		/* real UID of the task */
	kgid_t		gid;		/* real GID of the task */
	kuid_t		suid;		/* saved UID of the task */
	kgid_t		sgid;		/* saved GID of the task */
	kuid_t		euid;		/* effective UID of the task */
	kgid_t		egid;		/* effective GID of the task */
	kuid_t		fsuid;		/* UID for VFS ops */
	kgid_t		fsgid;		/* GID for VFS ops */
	unsigned	securebits;	/* SUID-less security management */
	kernel_cap_t	cap_inheritable; /* caps our children can inherit */
	kernel_cap_t	cap_permitted;	/* caps we're permitted */
	kernel_cap_t	cap_effective;	/* caps we can actually use */
	kernel_cap_t	cap_bset;	/* capability bounding set */
#ifdef CONFIG_KEYS
	unsigned char	jit_keyring;	/* default keyring to attach requested
					 * keys to */
	struct key __rcu *session_keyring; /* keyring inherited over fork */
	struct key	*process_keyring; /* keyring private to this process */
	struct key	*thread_keyring; /* keyring private to this thread */
	struct key	*request_key_auth; /* assumed request_key authority */
#endif
#ifdef CONFIG_SECURITY
	void		*security;	/* subjective LSM security */
#endif
	struct user_struct *user;	/* real user ID subscription */
	struct user_namespace *user_ns; /* user_ns the caps and keyrings are relative to. */
	struct group_info *group_info;	/* supplementary groups for euid/fsgid */
	struct rcu_head	rcu;		/* RCU deletion hook */
};

extern void __put_cred(struct cred *);

static inline void validate_creds(const struct cred *cred)
{
}

static inline struct cred *get_new_cred(struct cred *cred)
{
	atomic_inc(&cred->usage);
	return cred;
}

extern struct user_namespace init_user_ns;

#endif /* ! __LINUX_CRED_H__ */
