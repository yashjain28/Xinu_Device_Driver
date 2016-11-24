#include <xinu.h>
extern sid32 semadc;

void adchandler (uint32	xnum){

		struct dentry *devptr;
		struct adc_csreg *adccsregptr;
		int32 status;
		devptr=(struct dentry *)&devtab[ADC1];
		adccsregptr=(struct adc_csreg *)devptr->dvcsr;
		status=adccsregptr->irqStatus; // clear the pending event
		adccsregptr->irqStatus=status; //write will basically clear the event
		signal(semadc);
		kprintf("inside adchandler");

}