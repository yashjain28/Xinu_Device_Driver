#include <xinu.h>
extern sid32 semadc;
devcall adcread(struct dentry *devptr, char *buf, int32 count){

		struct adc_csreg *controlreg=(struct adc_csreg*)devptr->dvcsr;
		controlreg->stepEnable|=1;
		int32 fifodata,i;
		char buffer[1];

		int32 fcount=controlreg->fifoInfo[0].fifoCount;
		buffer[0]=(count+100);
		write(GPIOD,buffer,1);
		sleep(1);		
		//kprintf("inside read");
		wait(semadc);
		//kprintf("starting read");

		for(i=0;i<fcount;i++){
			fifodata=controlreg->fifoData0 & 0xFFF;
		//	kprintf("\nfifodata0: %d\t",fifodata);			
		}

		//kprintf("\tfifodata0: %d\t",fifodata);
		buf[0]=fifodata & 0xFF;
		buf[1]=(fifodata & 0xFF00)>>8;
		controlreg->fifoData0=0x0000;
		controlreg->stepEnable&=~1;
		//kprintf("\toutside adcread\t");
		buffer[0]=count;
		write(GPIOD,buffer,1);		
		return OK;
}