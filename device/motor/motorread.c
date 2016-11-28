#include <xinu.h>

devcall motorread(struct dentry *devptr,char *buf,int32 count){
	motorF[0] = 14;
	motorB[0] = 15;
	motorF[1] = 16;
	motorB[1] = 17;
	int32 m1pin1,m1pin2,m2pin1,m2pin2, motorstatus;
	m1pin1 = read(GPIOD,buf,motorF[0]);
	m1pin2 = read(GPIOD,buf,motorB[0]);
	m2pin1 = read(GPIOD,buf,motorF[1]);
	m2pin2 = read(GPIOD,buf,motorB[1]);
	/*writing in one integer motorNUMpinNUM 0000 both motor off || 0010 or 0001 motor 1 is active || 1000 or 0100 motor 1 is active
	1010 || 0101 || 1001 || 0110 both motors active: basically you can interpret the direction also ! */
	motorstatus=(m2pin2<<3)|(m2pin1<<2)|(m1pin2<<1)|(m1pin1);
	return motorstatus;
}