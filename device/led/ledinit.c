#include <xinu.h>

sid32 led_sem;
sid32 shared_switch;
int32 led_switch;

void configure_led_gpio_registers(int32 bit_to_set){
	struct gpiod *gpio1;

	gpio1 = (struct gpiod *)GPIO1_BASE_ADDRESS;
	
	//configure led interrupt on gpio1 pin XX
	bit_to_set = (0x1)<<bit_to_set;
	gpio1->gpio_risingdetect |= bit_to_set;
	gpio1->gpio_fallingdetect |= bit_to_set;
	gpio1->gpio_irqstatus_set_0 |= bit_to_set;
}

devcall	ledinit(
	  struct dentry	*devptr		/* Entry in device switch table	*/
	)
{
	led_switch = 0;
	led_sem = semcreate(0);
	shared_switch = semcreate(1);
	configure_led_gpio_registers(12);
	return OK;
}	