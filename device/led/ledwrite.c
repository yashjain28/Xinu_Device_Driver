#include <xinu.h>

extern sid32 led_sem;
extern sid32 shared_switch;
extern int32 led_switch;

devcall ledwrite(struct dentry *devptr,char *buf,uint32 count)
{
	int32 pinno = 13;
	wait(shared_switch);
		if(buf[0]=='O')
		{
			led_switch = 1;
			buf[0] = ((1*100)+pinno);
		}
		else
		{
			led_switch = 0;
			buf[0] = pinno;
		}
	signal(shared_switch);
	signal(led_sem);
	//kprintf("calling kickout \n");
	ledkickout();
	return OK;
}