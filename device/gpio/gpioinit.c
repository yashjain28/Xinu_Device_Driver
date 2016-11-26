#include <xinu.h>

#define CM_WKUP_GPIO0CLKCRTL 				  (0x44E00408)


//MACRO to read and write register
#define HWREG(n)	(*((volatile unsigned int *)(n)))

sid32 read_sem;

void clk_configure(){
	kprintf("intial clock configuration %x \n",HWREG(CM_WKUP_GPIO0CLKCRTL));
	HWREG(CM_WKUP_GPIO0CLKCRTL) &= ~0x40002;
	HWREG(CM_WKUP_GPIO0CLKCRTL) |=0x40002;
	kprintf("CM WKUP GPIO0 CLK CRTL %x \n",(HWREG(CM_WKUP_GPIO0CLKCRTL)));
}

void configure_gpio_registers(){
	struct gpiod *gpio0,*gpio1;
	int32 bit_to_set;

	gpio0 = (struct gpiod *)GPIO0_BASE_ADDRESS;
	gpio1 = (struct gpiod *)GPIO1_BASE_ADDRESS;
	
	//configure gpio1
	bit_to_set = (0x1)<<13;
	gpio1->gpio_risingdetect |= bit_to_set;
	gpio1->gpio_irqstatus_set_0 |= bit_to_set;
	//gpio1->gpio_irqawaken_0 |= bit_to_set;

	//kprintf("gpio irq status %x \n", gpio1->gpio_irqstatus_set_0);
	//kprintf("gpio rising edge %x \n ", gpio1->gpio_risingdetect);
}

int32 gpioinit(struct	dentry *devptr){
	struct	intc_csreg *csrptr = (struct intc_csreg *)0x48200000; 

	read_sem = semcreate(0);
	
	kprintf("gpio initialized \n");
	//clk_configure();
	configure_gpio_registers();
	csrptr->threshold = 0X0FF;
	set_evec( devptr->dvirq, (uint32)devptr->dvintr );
	csrptr->ilr[devptr->dvirq] &= ~(0x01);
	//csrptr->ilr[devptr->dvirq+1] &= ~(0x01);
	csrptr->ilr[devptr->dvirq] |= (0x0A<<2);
	
	return OK;
}