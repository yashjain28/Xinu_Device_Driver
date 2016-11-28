#include <xinu.h>
#define forwarddir 1
#define backwarddir -1
#define stopdir 0
#define motor1 0
#define motor2 1
void direction(int motornum,int dir) // forward is 1 backward is -1 and stop is 0
{
		int high=0,low=0;
		if(dir==1){
			high=100;
			low=0;
		}
		else if(dir==-1){
			high=0;
			low=100;
		}
		else{
			high=0;
			low=0;
		}
		buf[0] = (high + motorF[motornum]);
		write(GPIOD,buf,count);
		buf[0] = (low + motorB[motornum]);
		write(GPIOD,buf,count);
}
devcall motorwrite(struct dentry *devptr,char *buf,uint32 count)
{
	int32 motorF[2],motorB[2]; // index 0 for motor 1 and index 1 for motor 2
	motorF[0]=12;
	motorB[0]=14;
	motorF[1]=13;
	motorB[1]=15;
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