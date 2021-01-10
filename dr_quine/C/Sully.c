#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
int main(){
int i=5;
if(i<0)return 0;if(access("Sully_5.c",R_OK)!=-1)i--;char t[50];sprintf(t,"%s%d%s","Sully_",i,".c");int fd=open(t,O_CREAT|O_TRUNC|O_WRONLY,0644);char*a="#include%1$c<fcntl.h>%2$c#include%1$c<stdio.h>%2$c#include%1$c<string.h>%2$c#include%1$c<stdlib.h>%2$c#include%1$c<unistd.h>%2$cint main(){%2$cint i=%5$d;%2$cif(i<0)return 0;if(access(%3$cSully_5.c%3$c,R_OK)!=-1)i--;char t[50];sprintf(t,%3$c%%s%%d%%s%3$c,%3$cSully_%3$c,i,%3$c.c%3$c);int fd=open(t,O_CREAT|O_TRUNC|O_WRONLY,0644);char*a=%3$c%4$s%3$c;dprintf(fd,a,32,10,34,a,i);close(fd);char c[100];sprintf(c,%3$cgcc -Wall -Wextra -Werror Sully_%%1$d.c -o Sully_%%1$d%3$c,i);system(c);memset(c,0,100);sprintf(c,%3$c./Sully_%%d%3$c,i);if(i)system(c);}%2$c";dprintf(fd,a,32,10,34,a,i);close(fd);char c[100];sprintf(c,"gcc -Wall -Wextra -Werror Sully_%1$d.c -o Sully_%1$d",i);system(c);memset(c,0,100);sprintf(c,"./Sully_%d",i);if(i)system(c);}
