#include <xinu.h>

extern sid32 gpio_sem;
extern sid32 done_sem;
extern sid32 shared_switch;
extern int32 swtch;
extern int32 gpio_pin_number;

void gpiohandler_out(){
	struct gpiod *gpio1;
	gpio1 = (struct gpiod *)GPIO1_BASE_ADDRESS;
	int32 bit_to_set ;
	
	wait(done_sem);
	wait(shared_switch);
		//kprintf("writing to hardware %d  and pin number %d\n",swtch,gpio_pin_number);
		bit_to_set = (1<<gpio_pin_number);
		//kprintf("inside handler \n");
		gpio1->gpio_oe = gpio1->gpio_oe & (~bit_to_set);		
		gpio1->gpio_dataout &= ~(bit_to_set);
		if(swtch==1)
			gpio1->gpio_dataout |= (bit_to_set);
	signal(shared_switch);
	signal(gpio_sem);
	//kprintf("releasing locks in handler \n");
}