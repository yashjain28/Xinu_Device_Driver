

struct adc_csreg
{
	volatile uint32 revison;
	volatile uint32 reserve1[3];
	volatile uint32 sysconfig;
	volatile uint32 reserve2[4];
	volatile uint32 irqStatusRaw;
	volatile uint32 irqStatus;
	volatile uint32 irqEnableSet;	
	volatile uint32 irqEnableClr;
	volatile uint32 irqWakeup;
	volatile uint32 dmaEnableSet;
	volatile uint32 dmaEnableClr;
	volatile uint32 ctrl;
	volatile uint32 adcStat;
	volatile uint32 adcRange;
	volatile uint32 adcClkDiv;
	volatile uint32 adcMisc;
	volatile uint32 stepEnable;
	volatile uint32 idleConfig;
	volatile uint32 tsChargeStepconfig;
	volatile uint32 tsChargeDelay;
	struct 
	{
		volatile uint32 stepConfig;
		volatile uint32 stepDelay;
	}step[16];
	struct 
	{
		volatile uint32 fifoCount;
		volatile uint32 fifoThreshold;
		volatile uint32 dmaReq;
	}fifoInfo[2];
	volatile uint32 reserve3;
	volatile uint32 fifoData0;
	volatile uint32 reserve4[63];
	volatile uint32 fifoData1;
};
