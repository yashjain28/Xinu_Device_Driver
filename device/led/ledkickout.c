#include <xinu.h>

void ledkickout(){
	struct gpiod *gpio1;
	gpio1 = (struct gpiod *)GPIO1_BASE_ADDRESS;
	int32 bit_to_set = (1<<12),value;
	kprintf("inside kickout");
	gpio1->gpio_oe = gpio1->gpio_oe & (~bit_to_set);		
	value = gpio1->gpio_dataout & bit_to_set;
	if(value>>12 ==1)
		gpio1->gpio_dataout &= ~value;
	else
		gpio1->gpio_dataout |= bit_to_set;
}