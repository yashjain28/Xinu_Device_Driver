#include <xinu.h>

extern sid32 gpio_sem;
extern sid32 done_sem;
extern sid32 shared_switch;
extern int32 swtch;
extern int32 gpio_pin_number;

int32	gpiowrite (
		struct	dentry *devptr,
		void	*buf,
		uint32	count
	)
{
	// reads data from the buffer where data is in char msb is value and value%100 is pin number 
	// in 1 write 4 pins can be manipulated in gpio bank 
	int32 i=0,value,data,pinnumber;
	struct gpiod *gpio1;
	gpio1 = (struct gpiod *)GPIO1_BASE_ADDRESS;
	for(i=0;i<count;i++){
		//kprintf("acquiring gpio sem lock \n");
		wait(gpio_sem);
		//kprintf("acquiring lock \n");
		wait(shared_switch);

			data=*(((char *)buf)+i);
			value=data/100;
			pinnumber=data%100;
			swtch = value;
			gpio_pin_number = pinnumber;
		signal(shared_switch);
		signal(done_sem);
		//kprintf("released all locks\n");
		gpiokickout(12);
	}	
}