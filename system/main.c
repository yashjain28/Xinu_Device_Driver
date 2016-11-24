/*  main.c  - main */

#include <xinu.h>


process	main(void)
{
	recvclr();
	//resume(create(shell, 8192, 50, "shell", 1, CONSOLE));

	/* Wait for shell to exit and recreate it 

	while (TRUE) {
		receive();
		sleepms(200);
		kprintf("\n\nMain process recreating shell\n\n");
		resume(create(shell, 4096, 20, "shell", 1, CONSOLE));
	}
	*/
	char buf[4];
	int32 i=0;
	kprintf("start of main");
	for(i=0;i<10;i++){
		read(ADC, buf,4);
		sleep(2);	
	}
	read(ADC, buf,4);
	kprintf("end of main");

	return OK;
    
}
