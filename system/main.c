#include <xinu.h>

process main(void){
    char buf[1];

    buf[0] = 0;
    /*sleep(2);
    write(GPIOD,buf,1);
    int32 temp=read(TMPS,buf,2);
    kprintf("\ntemperatutre= %d",temp);
    sleep(30);
    temp=read(TMPS,buf,2);
    kprintf("\ntemperatutre= %d",temp);*/
    kprintf("sTARTING MOTOR CODE\n");
    sleep(3);
    write(MOTOR,buf,1);
    sleep(5);
    write(MOTOR,buf,2);
    sleep(5);
    write(MOTOR,buf,3);
    sleep(5);
    write(MOTOR,buf,4);
    sleep(5);
    write(MOTOR,buf,5);

    return OK;
}