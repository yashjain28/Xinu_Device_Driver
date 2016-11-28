#include <xinu.h>

sid32 led_sem;
sid32 shared_switch;
int32 led_switch;



devcall	ledinit(
	  struct dentry	*devptr		/* Entry in device switch table	*/
	)
{
	led_switch = 0;
	led_sem = semcreate(0);
	shared_switch = semcreate(1);
	return OK;
}	