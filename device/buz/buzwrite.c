#include <xinu.h>
devcall buzwrite(struct dentry *devptr,char *buf,uint32 count){
	int32 pinnum = 6;
	nokiatune(pinnum);
}