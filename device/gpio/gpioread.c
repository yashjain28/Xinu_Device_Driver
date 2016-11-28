#include <xinu.h>

extern sid32 read_sem;

devcall gpioread(struct dentry *devptr, char *buff, int32 count){
	struct gpiod *gpio,*gpio1;
	int data;
	gpio1 = (struct gpiod *)GPIO1_BASE_ADDRESS;
	//gpio1->gpio_oe |= 1<<count;
	//wait(read_sem);
	kprintf("inside read \n");
	
	
	//read from gpio bank
	data = gpio1->gpio_dataout;
	
	kprintf("gpio 1 value %d \n", data);
	if(data!=0)
		return 1;
	else 
		return 0;
	
}