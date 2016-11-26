#include <xinu.h>

extern sid32 read_sem;

void gpiohandler(uint32 xnum){
	struct	intc_csreg *csrptr = (struct intc_csreg *)0x48200000;
	int32 irqStatus;
	int32 bit_to_set;
	struct gpiod *gpio1;
	gpio1 = (struct gpiod *)GPIO1_BASE_ADDRESS;
	//irqStatus = gpio1->gpio_irqstatus_raw_0;     
	//gpio1->gpio_irqstatus_0 = irqStatus;
	//kprintf("interrupt disabled \n");
	signal(read_sem);
	csrptr->control |= (INTC_CONTROL_NEWIRQAGR);
}