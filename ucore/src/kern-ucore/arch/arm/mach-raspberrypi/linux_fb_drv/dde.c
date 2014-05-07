#include "dde.h"

#include <pmm.h>
#include <mailbox.h>
#include <slab.h>

#define ___GFP_ZERO 0x8000u
#define __GFP_ZERO	((gfp_t)___GFP_ZERO)	/* Return zeroed page on success */

void *dde_kmalloc(size_t size, gfp_t flags)
{
    kprintf("dde_kmalloc begin\n");
	void *ptr = kmalloc(size);
    kprintf("dde_kmalloc end\n");

	if (flags | __GFP_ZERO) {
        kprintf("memset begin\n");
		memset(ptr, 0, size);
        kprintf("memset end\n");
	}
	return ptr;
}

void *dde_kva_alloc_pages(size_t n, unsigned int flags)
{
	struct Page *pages = alloc_pages(n);
	if (!pages)
		return NULL;
	if (flags & UCORE_KAP_IO) {
		int i;
		for (i = 0; i < n; i++)
			SetPageIO(&pages[i]);
	}
	return page2kva(pages);
}


int dde_mailbox_read(unsigned int channel, uint32_t * data)
{
    unsigned int ret = readmailbox(channel);
    if (ret == 0xffffffff) return -1;
    *data = ret;
}
int dde_mailbox_write(unsigned int channel, uint32_t data)
{
    writemailbox(channel, data);
    return 0;
}
