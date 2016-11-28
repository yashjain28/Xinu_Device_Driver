#include <xinu.h>

devcall buzread(struct dentry *devptr, char *buf, int32 count){
	return read(BUZ,buf,count);
}