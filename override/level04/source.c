#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <sys/prctl.h>
#include <sys/ptrace.h>
#include <stdio.h>
#include <sys/wait.h>
#include <signal.h>

int main(void)
{
    int     pid;          /* esp + 0xac */
    int     var1;		  /* esp + 0xa8 */
    int     var2;		  /* esp + 0x1c */
    char    buffer[128];  /* esp + 0x20 */
	
    pid = fork();
    memset(buff, 0, 128);
    var1 = 0;
    var2 = 0;
    if (pid == 0)
    {
        prctl(1, 1);
        ptrace(0, 0, 0, 0)
        puts("Give me some shellcode, k");
        gets(&buffer);
        return (0);
    }
    while (1)
    {
        wait(&var2);
        if ((var2 & 0x7f) != 0 || (((var2 & 0x7f) + 1) / 2) > 0)
        {
            puts("child is exiting...");
            return (0);
        }
        var1 = ptrace(3, pid, 44, 0)
        if (var1 == 11)
            break;
    }
    puts("no exec() for you");
    kill(pid, 9);

    return (0);
}
