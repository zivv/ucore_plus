/*
 *  bootmain.c
 *  copy kernel image to ram
 *  kernel should be placed in first sector of SROM, which is INITIAL_LOAD
 *
 *  author: YU KuanLong / HE Alexis
 *  part of the code is written by WANG JianFei
 *  date:   2011-3-21
 */

#include "elf.h"
#include "barrier.h"

#define ELFHDR		((struct elfhdr *) (BOOTLOADER_BASE+0x1000))      // scratch space

#define PUT32(x,y) *((int*)x)=(y)
#define GET32(x) *((int*)x)
//extern void PUT32 ( unsigned int, unsigned int );
//extern unsigned int GET32 ( unsigned int );
extern void dummy ( unsigned int );
extern void __memcpy(void* va, void* count, uint32_t offset);

#define GPFSEL1 0x20200004
#define GPSET0 0x2020001C
#define GPCLR0 0x20200028
#define GPPUD 0x20200094
#define GPPUDCLK0 0x20200098

#define AUX_ENABLES 0x20215004
#define AUX_MU_IO_REG 0x20215040
#define AUX_MU_IER_REG 0x20215044
#define AUX_MU_IIR_REG 0x20215048
#define AUX_MU_LCR_REG 0x2021504C
#define AUX_MU_MCR_REG 0x20215050
#define AUX_MU_LSR_REG 0x20215054
#define AUX_MU_MSR_REG 0x20215058
#define AUX_MU_SCRATCH 0x2021505C
#define AUX_MU_CNTL_REG 0x20215060
#define AUX_MU_STAT_REG 0x20215064
#define AUX_MU_BAUD_REG 0x20215068

static void uart_putc0(unsigned int ch) {
  dmb();
  while(!(GET32(AUX_MU_LSR_REG)&0x20)) ;
  dmb();
  PUT32(AUX_MU_IO_REG,ch);
  dmb();
}

static void uart_putc ( unsigned int c )
{
  if (c=='\n' || c=='\r') {
    uart_putc0(0x0D);
    uart_putc0(0x0A);
  } else {
    uart_putc0(c);
  }
}

static void uart_puts(const char *p)
{
  while (*p)
    uart_putc(*p++);
}

/* *
 * CC
 * */
static void uart_putint(const int p) {
    int n = 0;
    int tmpp = p;
    while (tmpp) {
        ++n;
        tmpp /= 10;
    }
    while (n) {
        int i = 0;
        tmpp = p;
        for (; i < n-1; i++) {
            tmpp /= 10;
        }
        tmpp %= 10;
        uart_putc('0'+tmpp);
        --n;
    }
    uart_putc('\n');
}


/* *
 * readseg - read @count bytes at @offset from kernel into virtual address @va,
 * might copy more than asked.
 * */
static void
readseg(uintptr_t va, uint32_t count, uint32_t offset) {
  __memcpy((void*)va, (void*)((uint8_t*)ELFHDR + offset), count);
}

void
uart_init() {
  unsigned int ra;

  PUT32(AUX_ENABLES,1);
  PUT32(AUX_MU_CNTL_REG,0);
  PUT32(AUX_MU_LCR_REG,0x3); //different from manual
  PUT32(AUX_MU_MCR_REG,0);
  PUT32(AUX_MU_IER_REG,0x1); //enable uart rx interrupt (rx and tx on manual is probably reversed)
  PUT32(AUX_MU_IIR_REG,0xC6);
  PUT32(AUX_MU_BAUD_REG,270); //see BCM2835 manual section 2.2.1

  ra=GET32(GPFSEL1);
  ra&=~(7<<12); //gpio14
  ra|=2<<12; //alt5
  ra&=~(7<<15); //gpio15
  ra|=2<<15; //alt5
  PUT32(GPFSEL1,ra);

  PUT32(GPPUD,0);
  for(ra=0;ra<150;ra++) dummy(ra);
  PUT32(GPPUDCLK0,(1<<14)|(1<<15));
  for(ra=0;ra<150;ra++) dummy(ra);
  PUT32(GPPUDCLK0,0);

  PUT32(AUX_MU_CNTL_REG,3);
}

/* bootmain - the entry of bootloader */
void
bootmain(void) {
  uart_init();

  extern char __bss_start__[], __bss_end__[];
  char *ptr = __bss_start__;
  const char *booterror = "Unknown";
  for(;ptr<__bss_end__;ptr++)
    *ptr = 0;

  uart_puts("Booting, please wait...\n");

  // is this a valid ELF?
  if (ELFHDR->e_magic != ELF_MAGIC) {
    booterror = "Bad ELF Magic";
    goto bad;
  }

  struct proghdr *ph, *eph;

  // load each program segment (ignores ph flags)
  ph = (struct proghdr *)((uintptr_t)ELFHDR + ELFHDR->e_phoff);

  uart_puts("ELFHDR = ");
  uart_putint(ELFHDR);

  uart_puts("ph = ");
  uart_putint(ph);

  eph = ph + ELFHDR->e_phnum;

  uart_puts("eph = ");
  uart_putint(eph);

  uart_puts("for begin\n");
  for (; ph < eph; ph ++) {
    uart_puts("in for before readseg....\n");

    uart_puts("ph->p_va = ");
    uart_putint(ph->p_va&0xFFFFFF);
    uart_puts("ph->p_memsz = ");
    uart_putint(ph->p_memsz);
    uart_puts("ph->p_offset = ");
    uart_putint(ph->p_offset);

    readseg(ph->p_va &0xFFFFFF, ph->p_memsz, ph->p_offset);
    uart_puts("in for....\n");
  }
  uart_puts("for ends\n");

  // call the entry point from the ELF header
  // note: does not return
  uart_puts("Jump to kernel\n");
  uart_puts("e_entry = ");
  uart_putint(ELFHDR->e_entry&0xFFFFFF);
  ((void (*) (void))(ELFHDR->e_entry &0xffffff))();

bad:
  uart_puts("Error: ");
  uart_puts(booterror);
  uart_puts("\n");

  /* do nothing */
  while (1);
}

