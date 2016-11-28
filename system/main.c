#include <xinu.h>

process main(void){
    char buf[1];
    /*buf[0] = 115;
    sleep(2);
    write(GPIOD,buf,1);
    int32 temp=read(TMPS,buf,2);
    kprintf("\ntemperatutre= %d",temp);
    sleep(30);
    temp=read(TMPS,buf,2);
    kprintf("\ntemperatutre= %d",temp);*/
    kprintf("sTARTING MOTOR CODE\n");
    sleep(3);
    buf[0]="FORWARD";
    write(MOTOR,buf,1);
    sleep(5);
    buf[0]="BACKWARD";
    write(MOTOR,buf,1);
    sleep(5);
    buf[0]="LEFT";
    write(MOTOR,buf,1);
    sleep(5);
    buf[0]="RIGHT";
    write(MOTOR,buf,1);
    sleep(5);
    buf[0]="STOP";
    write(MOTOR,buf,1);

    return OK;
}