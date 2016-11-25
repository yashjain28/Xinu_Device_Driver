#include <xinu.h>
#define CM_PER                                (0x44E00000)		
#define CM_PER_L3S_CLKSTCTRL                  (0x44E00004)
#define CM_PER_L3_CLKSTCTRL                   (0x44E0000C)
#define CM_PER_L3_INSTR_CLKCTRL               (0x44E000DC)
#define CM_PER_L3_CLKCTRL                     (0x44E000E0)
#define CM_PER_OCPWP_L3_CLKSTCTRL             (0x44E0012C)

#define CM_WKUP                               (0x44E00400)		
#define CM_WKUP_CLKSTCTRL                     (0x44E00400)
#define CM_WKUP_CONTROL_CLKCTRL               (0x44E00404)
#define CM_WKUP_GPIO0CLKCRTL 				  (0x44E00408)
#define CM_WKUP_L4WKUP_CLKCTRL                (0x44E0040C)
#define CM_L3_AON_CLKSTCTRL                   (0x44E00418)
#define CM_WKUP_ADC_TSC_CLKCTRL               (0x44E004BC)
#define CM_WKUP_CM_L4_WKUP_AON_CLKSTCTRL      (0x44E004CC)

//Interrupt controller register (part)
#define INTERRUPT_CONTROLLER                  (0x48200000)
#define INTC_THRESHOLD                        (0x48200068)

//MACRO to read and write register
#define HWREG(n)	(*((volatile unsigned int *)(n)))

sid32 read_sem;
/*
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
/*
void InitialL3Clock()
{	
	HWREG(CM_PER_L3_CLKCTRL) |= 0x02;                                //wake up L3 clock control
	while(( HWREG(CM_PER_L3_CLKCTRL) & 0x03 ) != 0x02 );             //wait 

	HWREG(CM_PER_L3_INSTR_CLKCTRL) |= 0x02;                          //wake up L3 instr clock
	while(( HWREG(CM_PER_L3_INSTR_CLKCTRL) & 0x03 ) != 0x02 );       //wait

	HWREG(CM_PER_L3_CLKSTCTRL) |= 0x02;                              //wake up L3 st clock
	while(( HWREG(CM_PER_L3_CLKSTCTRL) & 0x03 ) != 0x02 );           //wait
		  
	HWREG(CM_PER_OCPWP_L3_CLKSTCTRL) |= 0x02;                        //wake up ocp L3 st clock
	while(( HWREG(CM_PER_OCPWP_L3_CLKSTCTRL) & 0x03 ) != 0x02 );     //wait

	HWREG(CM_PER_L3S_CLKSTCTRL) |= 0x02;                             //wake up L3s st clock
	while(( HWREG(CM_PER_L3S_CLKSTCTRL) & 0x03 ) != 0x02 );          //wait

	while(( HWREG(CM_PER_L3_CLKCTRL) & (0x03<<16) ) != 0x00 );        //wait L3 clock fully functional.
	while(( HWREG(CM_PER_L3_INSTR_CLKCTRL) & (0x03<<16) ) != 0x00 );  //wait L3 instr clock fully functional
	while(( HWREG(CM_PER_L3_CLKSTCTRL) & (0x01<<4) ) == 0x00 );       //wait L3_GCLK active
	while(( HWREG(CM_PER_OCPWP_L3_CLKSTCTRL) & (0x01<<4) ) == 0x00 ); //wait ocpwp L3_GCLK active	
	while(( HWREG(CM_PER_L3S_CLKSTCTRL) & (0x01<<3) ) == 0x00 );      //wait L3S GCLK active
}
*/

void clk_configure(){
	kprintf("intial clock configuration %x \n",HWREG(CM_WKUP_GPIO0CLKCRTL));
	HWREG(CM_WKUP_GPIO0CLKCRTL) &= ~0x40002;
	HWREG(CM_WKUP_GPIO0CLKCRTL) |=0x40002;
	kprintf("CM WKUP GPIO0 CLK CRTL %x \n",(HWREG(CM_WKUP_GPIO0CLKCRTL)));
}

void configure_gpio_registers(){
	struct gpiod *gpio0,*gpio1;
	int32 bit_to_set;

	gpio0 = (struct gpiod *)GPIO0_BASE_ADDRESS;
	gpio1 = (struct gpiod *)GPIO1_BASE_ADDRESS;
	//configure gpio0
	/*
	gpio0->gpio_risingdetect = 0xFFFFFFFF;
	gpio1->gpio_fallingdetect = 0xFFFFFFFF;
	//gpio0->gpio_leveldetect_0 = 0xFFFFFFFF;
	//gpio0->gpio_leveldetect_1 = 0xFFFFFFFF;
	gpio0->gpio_irqstatus_set_0 = 0xFFFFFFFF;
	gpio0->gpio_irqstatus_set_1 = 0xFFFFFFFF;
	gpio0->gpio_irqawaken_0 = 0xFFFFFFFF;
	gpio0->gpio_irqawaken_1 = 0xFFFFFFFF;
	//gpio0->gpio_debounceenable = 0xFFFFFFFF;
	gpio0->gpio_sysconfig |=  4;
	
	gpio0->gpio_oe = 0;
	gpio0->gpio_cleardataout = 0xFFFFFFFF;
	gpio0->gpio_oe = 0xFFFFFFFF;
	*/
	//gpio0->gpio_sysconfig |= 0x;
	//configure gpio1
	bit_to_set = (0x1)<<13;
	gpio1->gpio_risingdetect |= bit_to_set;
	gpio1->gpio_fallingdetect |= bit_to_set;
	//gpio1->gpio_leveldetect_0 = 0xFFFFFFFF;
	//gpio1->gpio_leveldetect_1 = 0xFFFFFFFF;
	gpio1->gpio_irqstatus_set_0 |= bit_to_set;
	//gpio1->gpio_irqstatus_set_1 |= bit_to_set;
	gpio1->gpio_irqawaken_0 |= bit_to_set;
	//gpio1->gpio_irqawaken_1 |= bit_to_set;
	//gpio1->gpio_sysconfig |=  4;

	gpio1->gpio_oe = 0;
	gpio1->gpio_cleardataout = 0xFFFFFFFF;
	gpio1->gpio_oe = 0xFFFFFFFF;

	kprintf("gpio irq status %x \n", gpio1->gpio_irqstatus_set_0);
	kprintf("gpio rising edge %x \n ", gpio1->gpio_risingdetect);
}

int32 gpioinit(struct	dentry *devptr){
	struct	intc_csreg *csrptr = (struct intc_csreg *)0x48200000; 

	read_sem = semcreate(0);
	
	kprintf("gpio initialized \n");
	//InitialL4Clock();
	//InitialL3Clock();
	clk_configure();
	configure_gpio_registers();
	csrptr->threshold = 0X0FF;
	set_evec( devptr->dvirq, (uint32)devptr->dvintr );
	csrptr->ilr[devptr->dvirq] &= ~(0x01);
	csrptr->ilr[devptr->dvirq+1] &= ~(0x01);
	csrptr->ilr[devptr->dvirq] |= (0x0A<<2);
	
	return OK;
}