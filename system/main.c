/*  main.c  - main */

#include <xinu.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>

int strcspn(char *string,char *chars)			
{
    char c, *p, *s;

    for (s = string, c = *s; c != 0; s++, c = *s) {
	for (p = chars; *p != 0; p++) {
	    if (c == *p) {
		return s-string;
	    }
	}
    }
    return s-string;
}

char * strtok(char *s,char *delim)  
{
    char *lasts;
    int ch;

    if (s == 0)
	s = lasts;
    do {
	if ((ch = *s++) == '\0')
	    return 0;
    } while (strchr(delim, ch));
    --s;
    lasts = s + strcspn(s, delim);
    if (*lasts != 0)
	*lasts++ = 0;
    return s;
}

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

int32 sum(char** str)
{
	int a = atoi(*(str));
    int b = atoi(*(str + 1));
    int c = a + b;
    return c;
}

int32 parse_data(char *buff)
{
    kprintf("Enter");
	int argc = 0;
	int i = 0;
	char* argv[10];
	//char delim = ' ';
	kprintf("%s",buff);
	char func_name[10];
	int ret;
		char* inp = strtok(buff,' ');
		strcpy(func_name,inp);
		while(inp)
		{
			inp = strtok(0,' ');
			argv[argc++] = inp;
		}
    argv[argc] = 0;

    if(!strcmp(func_name,"sum"))
    {
        ret = sum(argv);
    }
    return ret;
}

process	main(void)
{
	recvclr();
	char buff[100];
	char funcname[20];
	uid32 slot;
	uint32 remip;
	uint16 remport;
	int val;
	char op[2];
	while(1){
    udp_init();
    if ((slot = udp_register(0,0,22))!= SYSERR){
    	kprintf("REgistered");
    	if(udp_recvaddr(slot,&remip,&remport,&buff,100,1000) != SYSERR){
    	   	   kprintf("Receiving");
    	   	   kprintf("%s",buff);
    	   	   if(strlen(buff)>0){
    	   	   val = parse_data(buff);
    	   	   kprintf("%d",val);
    		   /* for(i=0;i<5;i++)
    		   {
    		   	kprintf("%c",buff[i]);
    		   	//return OK;
    		   }*/
    		   kprintf("%d,%d",remip,remport);
               itoa(val,op);
    		   if(udp_sendto(slot,remip,remport,&op,2)!= SYSERR)
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
