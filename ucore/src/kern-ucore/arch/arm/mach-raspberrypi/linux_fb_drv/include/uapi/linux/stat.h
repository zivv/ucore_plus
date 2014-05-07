#ifndef __UAPI_LINUX_STAT_H__
#define __UAPI_LINUX_STAT_H__

#define S_IFMT  00170000

#define S_IFLNK	 0120000
#define S_IFREG  0100000

#define S_IFDIR  0040000

#define S_ISUID  0004000
#define S_ISGID  0002000

#define S_ISLNK(m)	(((m) & S_IFMT) == S_IFLNK)
#define S_ISREG(m)	(((m) & S_IFMT) == S_IFREG)
#define S_ISDIR(m)	(((m) & S_IFMT) == S_IFDIR)

#define S_IXUSR 00100

#define S_IXGRP 00010

#define S_IXOTH 00001

#endif /* ! __UAPI_LINUX_STAT_H__ */
