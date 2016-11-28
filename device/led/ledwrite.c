#include <xinu.h>
devcall ledwrite(struct dentry *devptr,char *buf,uint32 count)
{
	int32 pinno = 13;
	if(!strcmp(buf,"ON"))
	{
		buf[0] = ((1*100)+pinno);
	}
	else if(!strcmp(buf,"OFF"))
	{
		buf[0] = pinno;
	}
	write(GPIOD,buf,count);
	return OK;
}