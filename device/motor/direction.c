#include <xinu.h>

void direction(int32 motornum, int32 dir) // forward is 1 backward is -1 and stop is 0
{

		int32 high=0,low=0;
		int32 count=1;
		char buf[1];
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