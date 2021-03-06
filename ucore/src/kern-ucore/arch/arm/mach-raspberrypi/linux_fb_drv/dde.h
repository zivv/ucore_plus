/**
 * Adapter to avoid name confliction
 *
 * for example:
 *  if we have a conflicting name 'xxx' from linux with ucore
 *  we can declare a 'dde_xxx' here
 *  and implement in dde.c using ucore's 'xxx' 
 *  then use 'dde_xxx' in dummy.c to implement 'xxx' in linux
 */

#ifndef DDE_H
#define DDE_H

#include <types.h>

#define UCORE_KAP_IO 0x00000001
#define WARN(...) kprintf(__VA_ARGS__)

typedef unsigned int gfp_t;

void *dde_kmalloc(size_t size, gfp_t flags);

void *dde_kva_alloc_pages(size_t n, unsigned int flags);

int dde_mailbox_read(unsigned int channel, uint32_t * data);
int dde_mailbox_write(unsigned int channel, uint32_t data);

#endif
