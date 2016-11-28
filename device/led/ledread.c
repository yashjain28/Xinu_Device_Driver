#include<xinu.h>

devcall ledread(struct dentry *devptr,char *buf,int32 count){
	count = 13;
	return read(GPIOD,buf,count);
}