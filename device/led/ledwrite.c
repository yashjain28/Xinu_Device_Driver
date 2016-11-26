#include <xinu.h>

devcall	ledwrite (struct	dentry *devptr, void *buf, uint32 count)
{
	gpiowrite(devptr,buf,count);
	return OK;
}	