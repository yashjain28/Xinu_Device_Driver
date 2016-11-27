#include <xinu.h>

extern sid32 led_sem;
extern sid32 shared_switch;
extern int32 led_switch;

void ledhandler_out(){
	struct gpiod *gpio1;
	gpio1 = (struct gpiod *)GPIO1_BASE_ADDRESS;
	int32 bit_to_set = (1<<13);
	//kprintf("writing to hardware %d \n",led_switch);
	wait(led_sem);
	wait(shared_switch);
		//kprintf("inside write \n");
		gpio1->gpio_oe = gpio1->gpio_oe & (~bit_to_set);		
		gpio1->gpio_dataout &= ~(bit_to_set);
		if(led_switch==1)
			gpio1->gpio_dataout |= (bit_to_set);
	signal(shared_switch);
}