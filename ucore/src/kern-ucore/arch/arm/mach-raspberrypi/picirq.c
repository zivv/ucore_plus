/*
 * See page 113 of BCM2835 ARM peripherals
 */
#include <stdlib.h>

#include <types.h>
#include <arm.h>
#include <drivers/picirq.h>
#include <clock.h>
#include <serial.h>
#include <intr.h>
#include <kio.h>
#include <assert.h>
#include <memlayout.h>

static bool did_init = 0;

#define IRQ_PENDING_BASIC 0x2000B200
#define IRQ_PENDING_1 0x2000B204
#define IRQ_PENDING_2 0x2000B208
#define IRQ_ENABLE_BASIC 0x2000B218
#define IRQ_ENABLE_1 0x2000B210
#define IRQ_ENABLE_2 0x2000B214
#define IRQ_DISABLE_BASIC 0x2000B224
#define IRQ_DISABLE_1 0x2000B21C
#define IRQ_DISABLE_2 0x2000B220

#define PENDING_BASIC_NR_IRQS 8
#define PENDING_1_NR_IRQS 32
#define PENDING_2_NR_IRQS 32

#define PENDING_1_BIT 8
#define PENDING_2_BIT 9

#define SHORTCUT_MASK 0x01ffc00
#define SHORTCUT_IGNORE_BITS 10
#define SHORTCUT_IGNORE_MASK 0xfffffc00
// shortcuts are GPU IRQ 7, 9, 10, 18, 19, 53, 54, 55, 56, 57, 62
static unsigned int shortcut_map[11] = {15, 17, 18, 26, 27, 61, 62, 63, 64, 65, 70};

#define NR_IRQS (PENDING_BASIC_NR_IRQS + PENDING_1_NR_IRQS + PENDING_2_NR_IRQS)

void pic_disable(unsigned int irq)
{
	if (irq < PENDING_BASIC_NR_IRQS) {
		outw(IRQ_DISABLE_BASIC, 1 << irq);
	} else if (irq < PENDING_BASIC_NR_IRQS+PENDING_1_NR_IRQS) {
		outw(IRQ_DISABLE_1, 1 << (irq-PENDING_BASIC_NR_IRQS));
	} else if (irq < NR_IRQS) {
		outw(IRQ_DISABLE_2, 1 << (irq-PENDING_BASIC_NR_IRQS-PENDING_1_NR_IRQS));
	} else {
		//for rationale, read top of this file
		kprintf("WARNING: pic_disable: irq>=%d\n", NR_IRQS);
	}
}

void pic_enable(unsigned int irq)
{
	if (irq < PENDING_BASIC_NR_IRQS) {
		outw(IRQ_ENABLE_BASIC, 1 << irq);
	} else if (irq < PENDING_BASIC_NR_IRQS+PENDING_1_NR_IRQS) {
		outw(IRQ_ENABLE_1, 1 << (irq-PENDING_BASIC_NR_IRQS));
	} else if (irq < NR_IRQS) {
		outw(IRQ_ENABLE_2, 1 << (irq-PENDING_BASIC_NR_IRQS-PENDING_1_NR_IRQS));
	} else {
		//for rationale, read top of this file
		kprintf("WARNING: pic_enable: irq>=%d\n", NR_IRQS);
	}
}

struct irq_action {
	ucore_irq_handler_t handler;
	void *opaque;
};

struct irq_action actions[NR_IRQS];

void register_irq(int irq, ucore_irq_handler_t handler, void *opaque)
{
	if (irq >= 0 && irq < NR_IRQS) {
		actions[irq].handler = handler;
		actions[irq].opaque = opaque;
	} else {
		//for rationale, read top of this file
		kprintf("WARNING: register_irq: invalid irq 0x%02x(%d)\n", irq, irq);
	}
}

void pic_init(void)
{
	if (did_init)
		return;

	did_init = 1;
	//disable all
	outw(IRQ_DISABLE_BASIC, ~0);
	outw(IRQ_DISABLE_1, ~0);
	outw(IRQ_DISABLE_2, ~0);
	//enable IRQ : done in entry.S
	kprintf("pic_init()\n");

}

void irq_handler()
{
	uint32_t pending0;
	while ((pending0 = inw(IRQ_PENDING_BASIC)) != 0) {
		uint32_t irq;
		uint32_t firstbit0 = __builtin_ctz(pending0);
		if (firstbit0 < PENDING_BASIC_NR_IRQS) {
			irq = firstbit0;
    } else if (pending0 & SHORTCUT_MASK) {
      irq = shortcut_map[__builtin_ctz(pending0&SHORTCUT_IGNORE_MASK) -
        SHORTCUT_IGNORE_BITS];
		} else if (firstbit0 == PENDING_1_BIT) {
			uint32_t pending1 = inw(IRQ_PENDING_1);
			uint32_t firstbit1 = __builtin_ctz(pending1);
      irq = firstbit1 + PENDING_BASIC_NR_IRQS;
		} else if (firstbit0 == PENDING_2_BIT) {
			uint32_t pending2 = inw(IRQ_PENDING_2);
			uint32_t firstbit2 = __builtin_ctz(pending2);
      irq = firstbit2 + PENDING_BASIC_NR_IRQS + PENDING_1_NR_IRQS;
		} else {
			panic("invalid basic pending register: 0x%08x\n",
			      pending0);
		}
    if (irq != 0) {  // irq 0 is used by timer, ignore this irq info
      kprintf("recieve irq 0x%02x(%d)\n", irq, irq);
    }
		if (actions[irq].handler) {
			(*actions[irq].handler) (irq, actions[irq].opaque);
		} else {
			panic("unknown irq 0x%02x(%d)\n", irq, irq);
			pic_disable(irq);
		}
	}
}

void irq_clear(unsigned int source)
{
  actions[source].handler = NULL;
  actions[source].opaque = NULL;
}
