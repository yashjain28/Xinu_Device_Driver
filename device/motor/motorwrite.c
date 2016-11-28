 #include <xinu.h>
 devcall motorwrite(struct dentry *devptr,char *buf,uint32 count)
 {

 	motorF[0]=14;
	motorB[0]=15;
	motorF[1]=16;
	motorB[1]=17;
 	count=1;

 	if(strcmp(buf,"FORWARD"))
 	{
 		direction(motor1,buf,forwarddir);
		direction(motor2,buf,forwarddir);		
 	}
 	else if(strcmp(buf,"BACKWARD"))
 	{
 		direction(motor1,buf,backwarddir);
 		direction(motor2,buf,backwarddir);
 	}
 	else if(strcmp(buf,"LEFT"))
 	{
 		direction(motor1,buf,stopdir);
 		direction(motor2,buf,forwarddir);
 	}
 	else if(strcmp(buf,"RIGHT"))
 	{
 		direction(motor1,buf,forwarddir);
 		direction(motor2,buf,stopdir);
 	}
 	else if(strcmp(buf,"STOP"))
 	{
 		direction(motor1,buf,stopdir);
 		direction(motor2,buf,stopdir);
 	}

 	return OK;

 }