#include <xinu.h>
#define forwarddir 1
#define backwarddir -1
#define stopdir 0
#define motor1 0
#define motor2 1

devcall motorwrite(struct dentry *devptr,char *buf,uint32 count)
{
	int32 motorF[2],motorB[2]; // index 0 for motor 1 and index 1 for motor 2
	motorF[0]=14;
	motorB[0]=15;
	motorF[1]=16;
	motorB[1]=17;
	count=1;
	if(!strcpy(buf,"FORWARD"))
	{
		direction(motor1,forwarddir);
		direction(motor2,forwarddir);		
	}
	else if(!strcpy(buf,"BACKWARD"))
	{
		direction(motor1,backwarddir);
		direction(motor2,backwarddir);
		
	}
	else if(!strcpy(buf,"LEFT"))
	{
		direction(motor1,stopdir);
		direction(motor2,forwarddir);

	}
	else if(!strcpy(buf,"RIGHT"))
	{
		direction(motor1,forwarddir);
		direction(motor2,stopdir);

	}
	else if(!strcpy(buf,"STOP"))
	{
		direction(motor1,stopdir);
		direction(motor2,stopdir);

	}
	return OK;
}