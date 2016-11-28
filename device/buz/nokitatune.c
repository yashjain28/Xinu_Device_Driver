#include <xinu.h>


void nokiatune(char pinnum){

	char buf[1];
	char pinhigh=(char)(((int32)pinnum)+100);
	char pinlow=(char)pinnum;

        int32 count=1;

	buf[0]=pinhigh;
        write(GPIOD,buf,count);
        sleepms(100);   
        buf[0]=pinlow;
        write(GPIOD,buf,count);
        sleepms(100);

        buf[0]=pinhigh;
        write(GPIOD,buf,count);
        sleepms(100);
        buf[0]=pinlow;
        write(GPIOD,buf,count);
        sleepms(100);

        buf[0]=pinhigh;
        write(GPIOD,buf,count);
        sleepms(100);   
        buf[0]=pinlow;
        write(GPIOD,buf,count);
        sleepms(400);


        buf[0]=pinhigh;
        write(GPIOD,buf,count);
        sleepms(400);   
        buf[0]=pinlow;
        write(GPIOD,buf,count);
        sleepms(100);


        buf[0]=pinhigh;
        write(GPIOD,buf,count);
        sleepms(400);   
        buf[0]=pinlow;
        write(GPIOD,buf,count);
        sleepms(100);
        
        buf[0]=pinhigh;
        write(GPIOD,buf,count);
        sleepms(100);   
        buf[0]=pinlow;
        write(GPIOD,buf,count);
        sleepms(100);

        buf[0]=pinhigh;
        write(GPIOD,buf,count);
        sleepms(100);   
        buf[0]=pinlow;
        write(GPIOD,buf,count);
        sleepms(100);
        
        buf[0]=pinhigh;
        write(GPIOD,buf,count);
        sleepms(100);   
        buf[0]=pinlow;
        write(GPIOD,buf,count);
        sleepms(100);
        
}