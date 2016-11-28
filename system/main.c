/*  main.c  - main */

#include <xinu.h>

void reverse(char s[])
 {
     int i, j;
     char c;

     for (i = 0, j = strlen(s)-1; i<j; i++, j--) {
         c = s[i];
         s[i] = s[j];
         s[j] = c;
     }
}  

 void itoa(int n, char s[])
 {
     int i, sign;

     if ((sign = n) < 0)  /* record sign */
         n = -n;          /* make n positive */
     i = 0;
     do {       /* generate digits in reverse order */
         s[i++] = n % 10 + '0';   /* get next digit */
     } while ((n /= 10) > 0);     /* delete it */
     if (sign < 0)
         s[i++] = '-';
     s[i] = '\0';
     reverse(s);
}

int32 parse_data(char *buff)
{
    int i = 0;
    int j = 0;
    char func_name[15];
    char temp[10];
    double ret;
    kprintf("%s",buff);
    while(buff[j] != ' ')
    {
        temp[i++] = buff[j++]; 
    }
    temp[i] = '\0';
    j = j + 1;
    int len = atoi(temp);
    int s = 0;
    i = 0;
    while(buff[j] != ' ')
    {
        s++;
        func_name[i++] = buff[j++];
    }
    s = s + 1;
    func_name[i] = '\0';
    j = j+1;
    char arg1[10];
    i = 0;
    while(s<len)
    {
        s++;
        arg1[i++] = buff[j++];
    }
    arg1[i] = '\0';
    if(!strcmp(func_name,"tmpsensor"))
    {
        if(!strcmp(arg1,"read")){
            char buff[4];
            ret = read(TMPS,&buff,4);
            return ret;
        }
    }
    else if(!strcmp(func_name,"led"))
    {
        ret = write(LED,&arg1,2);
        return ret;
    }
    else if(!strcmp(func_name,"motor"))
    {
        ret = write(MOTOR,&arg1,2);
        return ret;
    }
    else
    {
        return 0;
    }
}

process main(void)
{
    recvclr();
    char funcname[20];
    uid32 slot;
    uint32 remip;
    uint16 remport;
    int val;
    char op[10];
    while(1){
    udp_init();
    if ((slot = udp_register(0,0,22))!= SYSERR){
        char buff[100];
        if(udp_recvaddr(slot,&remip,&remport,&buff,100,1000) != SYSERR){
               if(strlen(buff)>0){
               val = parse_data(buff);
               kprintf("%d\n",val);
               itoa(val,op);
               kprintf("%s\n",op);
               if(udp_sendto(slot,remip,remport,&op,10)!= SYSERR)
               {
                kprintf("Sent!");
               }
               else{
                kprintf("SEnding error");
               }
            }
        }
        }
        else{
                kprintf("Error0");
        }
    }

    return OK;
}
