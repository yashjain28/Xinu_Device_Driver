#include <xinu.h>

extern sid32 read_sem;

devcall gpioread(struct dentry *devptr, char *buff, int32 count){
	struct gpiod *gpio,*gpio1;
	wait(read_sem);
	kprintf("inside read \n");
	gpio = (struct gpiod *)GPIO0_BASE_ADDRESS;
	gpio1 = (struct gpiod *)GPIO1_BASE_ADDRESS;
	gpio->gpio_oe &= 0;
	count = gpio->gpio_datain;
	kprintf("gpio 0 value %d \n", count);
	gpio1->gpio_oe &= 0;
	count = gpio1->gpio_datain;
	kprintf("gpio 1 value %d \n", count);

	
	kprintf("gpio irq status %x \n", gpio1->gpio_irqstatus_set_0);
	kprintf("gpio rising edge %x \n ", gpio1->gpio_risingdetect);

	/*gpio1->gpio_oe = 0;
	gpio1->gpio_cleardataout = 0xFFFFFFFF;
	gpio1->gpio_oe = 0xFFFFFFFF;*/
	return OK;
}