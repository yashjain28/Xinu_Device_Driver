#include <xinu.h>

extern sid32 read_sem;

devcall gpioread(struct dentry *devptr, char *buff, int32 count){
	struct gpiod *gpio,*gpio1;
	int data;
	wait(read_sem);
	//kprintf("inside read \n");
	gpio1 = (struct gpiod *)GPIO1_BASE_ADDRESS;
	
	//read from gpio bank
	gpio1->gpio_oe &= 0;
	data = gpio1->gpio_datain;
	
	kprintf("gpio 1 value %d \n", data);
	buff[3] = (data&(0xff000000))>>24;
	buff[2] = (data&(0x00ff0000))>>16;	
	buff[1] = (data&(0x0000ff00))>>8;
	buff[0] = (data&(0x000000ff));

	//kprintf("gpio irq status %x \n", gpio1->gpio_irqstatus_set_0);
	//kprintf("gpio rising edge %x \n ", gpio1->gpio_risingdetect);

	return OK;
}