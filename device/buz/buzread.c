#include <xinu.h>
devcall buzread(struct dentry *devptr, char *buf, int32 count){
	count = 6;
	return read(GPIOD,buf,count);
}