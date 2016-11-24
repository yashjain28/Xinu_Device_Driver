
#include <xinu.h>

//CLOCK domain register (part)
#define CM_PER                                (0x44E00000)		
#define CM_PER_L3S_CLKSTCTRL                  (0x44E00004)
#define CM_PER_L3_CLKSTCTRL                   (0x44E0000C)
#define CM_PER_L3_INSTR_CLKCTRL               (0x44E000DC)
#define CM_PER_L3_CLKCTRL                     (0x44E000E0)
#define CM_PER_OCPWP_L3_CLKSTCTRL             (0x44E0012C)

#define CM_WKUP                               (0x44E00400)		
#define CM_WKUP_CLKSTCTRL                     (0x44E00400)
#define CM_WKUP_CONTROL_CLKCTRL               (0x44E00404)
#define CM_WKUP_L4WKUP_CLKCTRL                (0x44E0040C)
#define CM_L3_AON_CLKSTCTRL                   (0x44E00418)
#define CM_WKUP_ADC_TSC_CLKCTRL               (0x44E004BC)
#define CM_WKUP_CM_L4_WKUP_AON_CLKSTCTRL      (0x44E004CC)

//Interrupt controller register (part)
#define INTERRUPT_CONTROLLER                  (0x48200000)
#define INTC_THRESHOLD                        (0x48200068)

//MACRO to read and write register
#define HWREG(n)	(*((volatile unsigned int *)(n)))

sid32 semadc;
void InitialL4Clock()
{


	HWREG(CM_WKUP_CONTROL_CLKCTRL) |= 0x02;                             //enbale wkup control clk
	while(( HWREG(CM_WKUP_CONTROL_CLKCTRL) & 0x03 ) != 0x02 );          //wait 

	HWREG(CM_WKUP_CLKSTCTRL) |= 0x02;                                   //enbale wkup st clk
	while(( HWREG(CM_WKUP_CLKSTCTRL) & 0x03 ) != 0x02 );                //wait 

	HWREG(CM_WKUP_CLKSTCTRL) |= 0x02;                                   //enbale wkup st clk
	while(( HWREG(CM_WKUP_CLKSTCTRL) & 0x03 ) != 0x02 );                //wait

	HWREG(CM_L3_AON_CLKSTCTRL) |= 0x02;                                 //enbale wkup st clk
	while(( HWREG(CM_L3_AON_CLKSTCTRL) & 0x03 ) != 0x02 );              //wait

	HWREG(CM_WKUP_ADC_TSC_CLKCTRL) |= 0x02;                             //enbale wkup st clk
	while(( HWREG(CM_WKUP_ADC_TSC_CLKCTRL) & 0x03 ) != 0x02 );          //wait

	while(( HWREG(CM_WKUP_CONTROL_CLKCTRL) & (0x03<<16) ) != 0x00 );            //wait wkup control clk fully functional
	while(( HWREG(CM_L3_AON_CLKSTCTRL) & (0x01<<3) ) == 0x00 );                 //wait L3 AON gclk active
	while(( HWREG(CM_WKUP_L4WKUP_CLKCTRL) & (0x03<<16) ) != 0x00 );             //wait L4 WKUP CLK fully functional
	while(( HWREG(CM_WKUP_CLKSTCTRL) & (0x01<<2) ) == 0x00 );                   //wait L4 WKUP GCLK active
	while(( HWREG(CM_WKUP_CM_L4_WKUP_AON_CLKSTCTRL) & (0x01<<2) ) == 0x00 );    //wait L4 WKUP aon CLK active
	while(( HWREG(CM_WKUP_CLKSTCTRL) & (0x01<<14) ) == 0x00 );                  //wait ADC fclk active
	while(( HWREG(CM_WKUP_ADC_TSC_CLKCTRL) & (0x03<<16) ) != 0x00 );            //wait ADC module fully functinoal
}

void initadcinterrupt(struct dentry *devptr){
	struct intc_csreg *intrptr=(struct intc_csreg *)0x48200000;
	intrptr->threshold = 0xFF;
	set_evec(devptr->dvirq,(uint32)devptr->dvintr);
	intrptr->ilr[devptr->dvirq] |=(0x0A)<<2;
}

void TestRegAddress(struct adc_csreg* pReg)
{
	kprintf("revison = %x, %x\r\n", (unsigned int)&pReg->revison,pReg->revison);
	kprintf("sysconfig = %x, %x\r\n", &pReg->sysconfig,pReg->sysconfig);
	kprintf("irqStatusRaw = %x, %x\r\n", (unsigned int)&pReg->irqStatusRaw,pReg->irqStatusRaw);
	kprintf("irqStatus = %x, %x\r\n", (unsigned int)&pReg->irqStatus,pReg->irqStatus);
	kprintf("irqEnableSet = %x, %x\r\n", (unsigned int)&pReg->irqEnableSet,pReg->irqEnableSet);	
	kprintf("irqEnableClr = %x, %x\r\n", (unsigned int)&pReg->irqEnableClr,pReg->irqEnableClr);
	kprintf("irqWakeup = %x, %x\r\n", (unsigned int)&pReg->irqWakeup,pReg->irqWakeup);
	kprintf("dmaEnableSet = %x, %x\r\n", (unsigned int)&pReg->dmaEnableSet,pReg->dmaEnableSet);
	kprintf("dmaEnableClr = %x, %x\r\n", (unsigned int)&pReg->dmaEnableClr,pReg->dmaEnableClr);
	kprintf("ctrl = %x, %x\r\n", (unsigned int)&pReg->ctrl,pReg->ctrl);
	kprintf("adcStat = %x, %x\r\n", (unsigned int)&pReg->adcStat,pReg->adcStat);
	kprintf("adcRange = %x, %x\r\n", (unsigned int)&pReg->adcRange,pReg->adcRange);
	kprintf("adcClkDiv = %x, %x\r\n", (unsigned int)&pReg->adcClkDiv,pReg->adcClkDiv);
	kprintf("adcMisc = %x, %x\r\n", (unsigned int)&pReg->adcMisc,pReg->adcMisc);
	kprintf("stepEnable = %x, %x\r\n", (unsigned int)&pReg->stepEnable,pReg->stepEnable);
	kprintf("idleConfig = %x, %x\r\n", (unsigned int)&pReg->idleConfig,pReg->idleConfig);
	kprintf("tsChargeStepconfig = %x, %x\r\n", (unsigned int)&pReg->tsChargeStepconfig,pReg->tsChargeStepconfig);
	kprintf("tsChargeDelay = %x, %x\r\n", (unsigned int)&pReg->tsChargeDelay,pReg->tsChargeDelay);
	int i=0;
	for(i=0;i<16;i++)
	{
		kprintf("stepConfig%d = %x, %x\r\n", i, (unsigned int)&pReg->step[i].stepConfig,pReg->step[i].stepConfig);
		kprintf("stepDelay%d = %x, %x\r\n", i, (unsigned int)&pReg->step[i].stepDelay,pReg->step[i].stepDelay);
	}
	for(i=0;i<2;i++)
	{
		kprintf("fifoCount%d = %x, %x\r\n", i,(unsigned int)&pReg->fifoInfo[i].fifoCount,pReg->fifoInfo[i].fifoCount);
		kprintf("fifoThreshold%d = %x, %x\r\n", i, (unsigned int)&pReg->fifoInfo[i].fifoThreshold,pReg->fifoInfo[i].fifoThreshold);
		kprintf("dmaReq%d = %x, %x\r\n", i, (unsigned int)&pReg->fifoInfo[i].dmaReq,pReg->fifoInfo[i].dmaReq);
	}
	kprintf("fifoData0 = %x, %x\r\n", (unsigned int)&pReg->fifoData0,pReg->fifoData0);
	kprintf("fifoData1 = %x, %x\r\n", (unsigned int)&pReg->fifoData1,pReg->fifoData1);

	int bank =16;
	struct	intc_csreg *csrptr = (struct intc_csreg *)0x48200000;
	//kprintf("pending irq = %x\r\n",csrptr->);
	kprintf("ITR = %x\r\n",csrptr->banks[bank].itr);
	kprintf("mir = %x\r\n",csrptr->banks[bank].mir);
	kprintf("mir_clear = %x\r\n",csrptr->banks[bank].mir_clear);
	kprintf("mir_set = %x\r\n",csrptr->banks[bank].mir_set);
	kprintf("isr_set = %x\r\n",csrptr->banks[bank].isr_set);
	kprintf("isr_clear = %x\r\n",csrptr->banks[bank].isr_clear);
	kprintf("pending_irq = %x\r\n",csrptr->banks[bank].pending_irq);
	kprintf("pending_fiq = %x\r\n",csrptr->banks[bank].pending_fiq);
}

void ADCStepConfig(struct adc_csreg *pReg, unsigned int stepSelect, 
					unsigned int positiveChannel,unsigned int positiveRef,
					unsigned int negativeChannel,unsigned int negativeRef)
{
	//configure the nagtive reference
	pReg->step[stepSelect].stepConfig &= ~ SEL_RFM_SWC_CLEAR;                //clear
	pReg->step[stepSelect].stepConfig |= negativeRef<<SEL_RFM_SWC_SHIFT;     //write

	//configure the positive input channel
	pReg->step[stepSelect].stepConfig &= ~ SEL_INP_SWC_CLEAR;                //clear
	pReg->step[stepSelect].stepConfig |= positiveChannel<<SEL_INP_SWC_SHIFT; //write

	//configure the negative input channel,
	pReg->step[stepSelect].stepConfig &= ~ SEL_INM_SWC_CLEAR;                //clear
	pReg->step[stepSelect].stepConfig |= negativeChannel<<SEL_INM_SWC_SHIFT; //write

	//configure the positive reference
	pReg->step[stepSelect].stepConfig &= ~ SEL_RFP_SWC_CLEAR;                 //clear
	pReg->step[stepSelect].stepConfig |= positiveRef<<SEL_RFP_SWC_SHIFT;      //write
}

void ADCStepAnalogSupplyConfig(struct adc_csreg *pReg, unsigned int stepSelect,
									unsigned int xppsw, unsigned int xnpsw, unsigned int yppsw)
{
	pReg->step[stepSelect].stepConfig &= ~ ADC_STEPCONFIG_XPPSW_SWC_CLEAR;
	pReg->step[stepSelect].stepConfig |= xppsw<<ADC_STEPCONFIG_XPPSW_SWC_SHIFT;

	pReg->step[stepSelect].stepConfig &= ~ ADC_STEPCONFIG_XNPSW_SWC_CLEAR;
	pReg->step[stepSelect].stepConfig |= xnpsw<<ADC_STEPCONFIG_XNPSW_SWC_SHIFT;

	pReg->step[stepSelect].stepConfig &= ~ ADC_STEPCONFIG_YPPSW_SWC_CLEAR;
	pReg->step[stepSelect].stepConfig |= yppsw<<ADC_STEPCONFIG_YPPSW_SWC_SHIFT;
}

void ADCStepAnalogGroundConfig(struct adc_csreg *pReg, unsigned int stepSelect,
								 unsigned int xnnsw,unsigned int ypnsw, unsigned int ynnsw,
                                 unsigned int wpnsw)
{
	pReg->step[stepSelect].stepConfig &= ~ ADC_STEPCONFIG_XNNSW_SWC_CLEAR;
	pReg->step[stepSelect].stepConfig |=  xnnsw<<ADC_STEPCONFIG_XNNSW_SWC_SHIFT;

	pReg->step[stepSelect].stepConfig &= ~ ADC_STEPCONFIG_YPNSW_SWC_CLEAR;
	pReg->step[stepSelect].stepConfig |=  ypnsw<<ADC_STEPCONFIG_YPNSW_SWC_SHIFT;

	pReg->step[stepSelect].stepConfig &= ~ ADC_STEPCONFIG_YNNSW_SWC_CLEAR;
	pReg->step[stepSelect].stepConfig |=  ynnsw<<ADC_STEPCONFIG_YPNSW_SWC_SHIFT;

	pReg->step[stepSelect].stepConfig &= ~ ADC_STEPCONFIG_WPNSW_SWC_CLEAR;
	pReg->step[stepSelect].stepConfig |=  wpnsw<<ADC_STEPCONFIG_WPNSW_SWC_SHIFT;	
}

devcall adcinit(struct dentry *devptr){
	kprintf("\nStarted adcinit\t");
	int32 *clockwakeup=(int32 *)CM_WKUP_ADC_TSC_CLKCTRL;
	struct adc_csreg *controlreg=(struct adc_csreg*)devptr->dvcsr;
	int32 v=1;
	
	semadc=semcreate(0);
	InitialL4Clock();
	initadcinterrupt(devptr);
	//*clockwakeup|=0x02;
	kprintf("1\t");
	//config adc clock
	controlreg->adcClkDiv&=~(0xffff);
	controlreg->adcClkDiv|=7;
	//make step config write protect
	controlreg->ctrl&=(0x01<<2);
	controlreg->ctrl|=(1<<2);

	// adc step operation mode control
	controlreg->step[0].stepConfig&=~(1<<25);
	//fifoselect 26th bit 





	controlreg->stepEnable|=0x02;
	kprintf("2");
	
	ADCStepConfig(controlreg,0,0,0,0,0);
	ADCStepAnalogSupplyConfig(controlreg, 0, 0, 0, 0);
	ADCStepAnalogGroundConfig(controlreg, 0, 0, 0, 0, 0);

	//step mode config, continuous mode
	controlreg->step[0].stepConfig &= ~(0x3);
	controlreg->step[0].stepConfig|=0x01;
	//average samples
	controlreg->step[0].stepConfig |= (0x4<<2);
	
	//workmode config
	controlreg->ctrl&=~(0x03<<5);
	//controlreg->ctrl|=0<<5;
	
	controlreg->irqStatus |= 0x7FFF;
	controlreg->irqEnableSet|=2;
	controlreg->ctrl |=1;
	kprintf("adcinitialized\t\n");
	TestRegAddress(controlreg);
	return OK;
}

