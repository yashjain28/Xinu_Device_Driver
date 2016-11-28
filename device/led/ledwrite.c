#include <xinu.h>

devcall ledwrite(struct dentry *devptr,char *buf,uint32 count)
{
	int32 pinno = 13;
	if(buf[0]=='O')
	{
		buf[0] = ((1*100)+pinno);
	}
	else
	{
		buf[0] = pinno;
	}
	//kprintf("calling kickout \n");
	write(GPIOD,buf,1);
	return OK;
}