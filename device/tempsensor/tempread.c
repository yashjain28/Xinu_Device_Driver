#include <xinu.h>
devcall tempread(struct dentry *devptr,char* buf,int32 count){
	int32 pinno = 7;
	read(ADC,buf,pinno);
	int16 data;
	int16 temp;
	int32 tempx100;
	float temperatureval = 0;

	data = buf[1]; 
	 temp = buf[0];
	temp = (data<<8)|temp;
	//if high voltage is 3.3, if its 5 mulitply by 5.0; 
	 temperatureval = ((((temp*1.0/4096.0)*1800.0)-500.0)/10.0);
	 tempx100 = (int32)(temperatureval*100);
	return tempx100;
}