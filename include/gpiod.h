#define GPIO0_BASE_ADDRESS 0x44E07000
#define GPIO1_BASE_ADDRESS 0x4804C000

#define GPIO_OE 0x134
#define GPIO_DATAOUT 0x13C
#define GPIO_RISING_EDGE 0x148

struct gpiod {
	uint32 gpio_revision; 
	uint32 res1[3];
	uint32 gpio_sysconfig;
	uint32 res2[3];
	uint32 gpio_eoi;
	uint32 gpio_irqstatus_raw_0;
	uint32 gpio_irqstatus_raw_1;
	uint32 gpio_irqstatus_0;
	uint32 gpio_irqstatus_1;
	uint32 gpio_irqstatus_set_0;
	uint32 gpio_irqstatus_set_1;
	uint32 gpio_irqstatus_clr_0;
	uint32 gpio_irqstatus_clr_1;
	uint32 gpio_irqawaken_0;
	uint32 gpio_irqawaken_1;
	uint32 res3[50];
	uint32 gpio_sysstatus;
	uint32 res4[6];
	uint32 gpio_ctrl;
	uint32 gpio_oe;
	uint32 gpio_datain;
	uint32 gpio_dataout;
	uint32 gpio_leveldetect_0;
	uint32 gpio_leveldetect_1;
	uint32 gpio_risingdetect;
	uint32 gpio_fallingdetect;
	uint32 gpio_debounceenable;
	uint32 gpio_debouncingtime;
	uint32 res5[14];
	uint32 gpio_cleardataout;
	uint32 gpio_setdataout;
};

