#include <xinu.h>
devcall motorwrite(struct dentry *devptr,char *buf,uint32 count)
{
	int32 motorF[2],motorB[2];//index 0 for motor 1 and index 1 for motor 2
	motorF[0] = 14;
	motorB[0] = 16;
	motorF[1] = 16;
	motorB[1] = 17;
	if(count == 1)
	{
		direction(motor1,forwarddir);
		direction(motor2,forwarddir);
	}
	else if(count == 2)
	{
		direction(motor1,backwarddir);
		direction(motor2,backwarddir);
	}
	else if(count == 3)
	{
		direction(motor1,stopdir);
		direction(motor2,forwarddir);
	}
	else if(count == 4)
	{
		direction(motor1,forwarddir);
		direction(motor2,stopdir);
	}
	else if(count == 5)
	{
		direction(motor1,stopdir);
		direction(motor2,stopdir);
	}
	return OK;
}