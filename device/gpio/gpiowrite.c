#include <xinu.h>

/*------------------------------------------------------------------------
 * ethwrite - enqueue a packet for transmission on TI AM335X Ethernet
 *------------------------------------------------------------------------
 */
int32	gpiowrite (
		struct	dentry *devptr,
		void	*buf,
		uint32	count
	)
{
	int32 mask;
	struct gpiod *gpio0,*gpio1;
	kprintf("inside write \n");

	gpio0 = (struct gpiod *)GPIO0_BASE_ADDRESS;
	gpio1 = (struct gpiod *)GPIO1_BASE_ADDRESS;
	gpio0->gpio_oe = gpio0->gpio_oe & (~(count));
	gpio0->gpio_dataout = gpio0->gpio_dataout | count;
	
	gpio0->gpio_irqstatus_raw_0 |= count;
	gpio0->gpio_irqstatus_raw_1 |= count; 
	
	
	gpio1->gpio_oe = gpio1->gpio_oe & (~(count));
	gpio1->gpio_dataout = gpio1->gpio_dataout | count;
}