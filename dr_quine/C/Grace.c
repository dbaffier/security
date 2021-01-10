#include <fcntl.h>
#include <stdio.h>
/*A*/
#define B
#define C
#define m() int main(){int fd=open("Grace_kid.c",O_CREAT|O_TRUNC|O_WRONLY,0644);char*a="#include%c<fcntl.h>%c#include%c<stdio.h>%c/*A*/%c#define%cB%c#define%cC%c#define%cm()%cint%cmain(){int%cfd=open(%cGrace_kid.c%c,O_CREAT|O_TRUNC|O_WRONLY,0644);char*a=%c%s%c;dprintf(fd,a,32,10,32,10,10,32,10,32,10,32,32,32,32,34,34,34,a,34,10,10);return 0;}%cm();%c";dprintf(fd,a,32,10,32,10,10,32,10,32,10,32,32,32,32,34,34,34,a,34,10,10);return 0;}
m();
