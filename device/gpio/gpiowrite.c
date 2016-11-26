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
	int32 i=0,value,data,pinnumber;
	struct gpiod *gpio1;
	kprintf("inside write \t");

	gpio1 = (struct gpiod *)GPIO1_BASE_ADDRESS;
	for(i=0;i<count;i++){
		data=*(((char *)buf)+i);
		value=data/100;
		pinnumber=data%100;
		kprintf("data %d val %d pinnum %d\t",data,value,pinnumber);
		gpio1->gpio_oe = gpio1->gpio_oe & (~(1<<pinnumber));		
		value=value<<pinnumber;
		kprintf("bef reset %d\t",gpio1->gpio_dataout);
		gpio1->gpio_dataout&=~(1<<pinnumber);
		kprintf("after %d\t",gpio1->gpio_dataout);
		gpio1->gpio_dataout |= value;
		kprintf("gpiowrite value %d\t",gpio1->gpio_dataout);
	}
		kprintf("\n");
	


}