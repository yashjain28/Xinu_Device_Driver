#include <xinu.h>

void main(){
    char buf[2];
    buf[0] = 115;
    sleep(2);
    write(GPIOD,buf,1);
    int32 temp=read(TMPS,buf,2);
    kprintf("\ntemperatutre= %d",temp);
    sleep(30);
    temp=read(TMPS,buf,2);
    kprintf("\ntemperatutre= %d",temp);
}