#include <xinu.h>

void gpiokickout(int32 pin_num){
	struct gpiod *gpio1;
	gpio1 = (struct gpiod *)GPIO1_BASE_ADDRESS;
	int32 bit_to_set = (1<<pin_num),value;
	kprintf("inside kickout \n");
	gpio1->gpio_oe = gpio1->gpio_oe & (~bit_to_set);		
	value = gpio1->gpio_dataout & bit_to_set;
	if(value>>pin_num ==1)
		gpio1->gpio_dataout &= ~value;
	else
		gpio1->gpio_dataout |= bit_to_set;
}