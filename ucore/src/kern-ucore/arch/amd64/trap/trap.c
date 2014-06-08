#include <types.h>
#include <mmu.h>
#include <memlayout.h>
#include <trap.h>
#include <arch.h>
#include <stdio.h>
#include <kdebug.h>
#include <assert.h>
#include <sync.h>
#include <monitor.h>
#include <vmm.h>
#include <proc.h>
#include <sched.h>
#include <unistd.h>
#include <syscall.h>
#include <error.h>
#include <kio.h>
#include <clock.h>
#include <intr.h>
#include <mp.h>
#include <ioapic.h>
#include <sysconf.h>
#include <refcache.h>

#define TICK_NUM 30

static struct gatedesc idt[256] = { {0} };

struct pseudodesc idt_pd = {
	sizeof(idt) - 1, (uintptr_t) idt
};

void idt_init(void)
{
	extern uintptr_t __vectors[];
	int i;
	for (i = 0; i < sizeof(idt) / sizeof(struct gatedesc); i++) {
		SETGATE(idt[i], 0, GD_KTEXT, __vectors[i], DPL_KERNEL);
	}
	SETGATE(idt[T_SYSCALL], 0, GD_KTEXT, __vectors[T_SYSCALL], DPL_USER);
	SETGATE(idt[T_IPI], 0, GD_KTEXT, __vectors[T_IPI], DPL_USER);
	SETGATE(idt[T_IPI_DOS], 0, GD_KTEXT, __vectors[T_IPI_DOS], DPL_USER);
	lidt(&idt_pd);
}

static const char *trapname(int trapno)
{
	static const char *const excnames[] = {
		"Divide error",
		"Debug",
		"Non-Maskable Interrupt",
		"Breakpoint",
		"Overflow",
		"BOUND Range Exceeded",
		"Invalid Opcode",
		"Device Not Available",
		"Double Fault",
		"Coprocessor Segment Overrun",
		"Invalid TSS",
		"Segment Not Present",
		"Stack Fault",
		"General Protection",
		"Page Fault",
		"(unknown trap)",
		"x87 FPU Floating-Point Error",
		"Alignment Check",
		"Machine-Check",
		"SIMD Floating-Point Exception"
	};

	if (trapno < sizeof(excnames) / sizeof(const char *const)) {
		return excnames[trapno];
	}
	if (trapno == T_SYSCALL) {
		return "System call";
	}
	if (trapno >= IRQ_OFFSET && trapno < IRQ_OFFSET + 16) {
		return "Hardware Interrupt";
	}
	return "(unknown trap)";
}

bool trap_in_kernel(struct trapframe * tf)
{
	return (tf->tf_cs == (uint16_t) KERNEL_CS);
}

static const char *IA32flags[] = {
	"CF", NULL, "PF", NULL, "AF", NULL, "ZF", "SF",
	"TF", "IF", "DF", "OF", NULL, NULL, "NT", NULL,
	"RF", "VM", "AC", "VIF", "VIP", "ID", NULL, NULL,
};

void print_trapframe(struct trapframe *tf)
{
	kprintf("trapframe at %p\n", tf);
	print_regs(&tf->tf_regs);
	kprintf("  trap 0x--------%08x %s\n", tf->tf_trapno,
		trapname(tf->tf_trapno));
	kprintf("  err  0x%016llx\n", tf->tf_err);
	kprintf("  rip  0x%016llx\n", tf->tf_rip);
	kprintf("  cs   0x------------%04x\n", tf->tf_cs);
	kprintf("  ds   0x------------%04x\n", tf->tf_ds);
	kprintf("  es   0x------------%04x\n", tf->tf_es);
	kprintf("  flag 0x%016llx\n", tf->tf_rflags);
	kprintf("  rsp  0x%016llx\n", tf->tf_rsp);
	kprintf("  ss   0x------------%04x\n", tf->tf_ss);

	int i, j;
	for (i = 0, j = 1; i < sizeof(IA32flags) / sizeof(IA32flags[0]);
	     i++, j <<= 1) {
		if ((tf->tf_rflags & j) && IA32flags[i] != NULL) {
			kprintf("%s,", IA32flags[i]);
		}
	}
	kprintf("IOPL=%d\n", (tf->tf_rflags & FL_IOPL_MASK) >> 12);
}

void print_regs(struct pushregs *regs)
{
	kprintf("  rdi  0x%016llx\n", regs->reg_rdi);
	kprintf("  rsi  0x%016llx\n", regs->reg_rsi);
	kprintf("  rdx  0x%016llx\n", regs->reg_rdx);
	kprintf("  rcx  0x%016llx\n", regs->reg_rcx);
	kprintf("  rax  0x%016llx\n", regs->reg_rax);
	kprintf("  r8   0x%016llx\n", regs->reg_r8);
	kprintf("  r9   0x%016llx\n", regs->reg_r9);
	kprintf("  r10  0x%016llx\n", regs->reg_r10);
	kprintf("  r11  0x%016llx\n", regs->reg_r11);
	kprintf("  rbx  0x%016llx\n", regs->reg_rbx);
	kprintf("  rbp  0x%016llx\n", regs->reg_rbp);
	kprintf("  r12  0x%016llx\n", regs->reg_r12);
	kprintf("  r13  0x%016llx\n", regs->reg_r13);
	kprintf("  r14  0x%016llx\n", regs->reg_r14);
	kprintf("  r15  0x%016llx\n", regs->reg_r15);
}

void trap(struct trapframe *tf)
{
  extern struct trapframe* irq_tf;
  irq_tf = tf;
	// used for previous projects
	if (current == NULL) {
    irq_handler();
	} else {
		// keep a trapframe chain in stack
		struct trapframe *otf = current->tf;
		current->tf = tf;

		bool in_kernel = trap_in_kernel(tf);
		if (!in_kernel || (current == idleproc && otf == NULL))
			kern_enter(tf->tf_trapno + 1000);

		// kprintf("%d %d {{{\n", lapic_id, current->pid);
    irq_handler();
		in_kernel = trap_in_kernel(current->tf);
		// kprintf("%d %d |||\n", lapic_id, current->pid);

		current->tf = otf;
		if (!in_kernel) {
			may_killed();
			if (current->need_resched) {
				schedule();
			}
		} else if (current == idleproc) {
			schedule();
		}
		// kprintf("%d %d }}}\n", lapic_id, current->pid);
		if (!in_kernel || (current == idleproc && otf == NULL))
			kern_leave();
	}
}

int ucore_in_interrupt()
{
	return 0;
}

void irq_enable(int irq_no)
{
	//XXX
	ioapic_enable(0, irq_no, 0);
}

void irq_disable(int irq_no)
{
	//XXX
	ioapic_disable(0, irq_no);
}

int tlbflush_handler(int irq, void* data) {
  lcr3(rcr3());	
  return 0;
}

void trap_init(void)
{
	//XXX
	if(!sysconf.lioapic_count)
		return;
	irq_enable(IRQ_KBD);
	irq_enable(IRQ_COM1);

  register_irq(T_TLBFLUSH, tlbflush_handler, NULL);
}
