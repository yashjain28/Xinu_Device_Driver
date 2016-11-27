#include <xinu.h>

extern sid32 read_sem;

devcall gpioread(struct dentry *devptr, char *buff, int32 count){
	struct gpiod *gpio,*gpio1;
	int data;
	gpio1 = (struct gpiod *)GPIO1_BASE_ADDRESS;
	gpio1->gpio_oe |= 1<<count;
	wait(read_sem);
	kprintf("inside read \n");
	
	
	//read from gpio bank
	data = gpio1->gpio_datain;
	
	kprintf("gpio 1 value %d \n", data);
	data = data&(1<<count);
	buff[0] = (data>>count);

	//kprintf("gpio irq status %x \n", gpio1->gpio_irqstatus_set_0);
	//kprintf("gpio rising edge %x \n ", gpio1->gpio_risingdetect);

	return OK;
}