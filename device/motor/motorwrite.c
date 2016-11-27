#include <xinu.h>
devcall motorwrite(struct dentry *devptr,char *buf,uint32 count)
{
	int32 pinno = 15;
	if(!strcpy(buf,"ON"))
	{
		buf[0] = ((1*100)+pinno);
	}
	else if(!strcpy(buf,"OFF"))
	{
		buf[0] = pinno;
	}
	write(GPIOD,buf,count);
	return OK;
}