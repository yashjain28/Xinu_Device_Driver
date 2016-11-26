#include <xinu.h>

devcall	motorwrite (struct	dentry *devptr, void *buf, uint32 count)
{
	gpiowrite(devptr,buf,count);
	return OK;
}	