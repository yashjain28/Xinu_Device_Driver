#include <xinu.h>

devcall ledread(struct dentry *devptr, char *buf, int32 count){
	return read(LED,buf,count);
}