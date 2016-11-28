//on board device application file: demo which invokes high level device calls of all the devices used.
#include <xinu.h>

process onboardapp(void)
{
	recvclr();
	//tempsensor read
	char* buff;
	int32 temperature = read(TMPS,&buff,4);
	//led read
	int32 ledstatus = read(LED,&buff,4);
	//led write
	int32 ledwrite = write(LED,"ON",2);
	//motor write
	//can move FORWARD,BACKWARD,STOP,LEFT,RIGHT
	int count = FORWARD;
	int32 motorwrite = write(MOTOR,"FORWARD",count);
	//motor read
	int32 motorstatus = read(LED,&buff,4);
	//buzz read
	int32 buzzstatus = read(BUZ,"read",4);
	//buzz write
	int32 buzzwrite = write(BUZ,"write",5);
          
    return OK;

}