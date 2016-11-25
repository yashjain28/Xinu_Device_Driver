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
	struct gpiod *gpio1;
	kprintf("inside write \n");
	
	gpio1 = (struct gpiod *)GPIO1_BASE_ADDRESS;
	
	gpio1->gpio_oe = gpio1->gpio_oe & (~(count));
	gpio1->gpio_dataout = gpio1->gpio_dataout | count;
}