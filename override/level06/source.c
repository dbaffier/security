#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/ptrace.h>

int		auth(char buff[32], unsigned int serial)
{
						        /* $ebp + 0x8 == BUFF */
	int		size;	    	    /* $ebp - 0xc         */
	int		n;			        /* $ebp - 0x10        */
	int		i;			        /* $ebp - 0x14        */

	buff[strcspn(buff, "\n")] = 0;

	size = strnlen(buff, 32);
	if (size == 5)
		return (1);
	if (ptrace(0, 0, 1, 0) == -1)
	{
		puts("\033[32m.---------------------------.");
		puts("\033[31m| !! TAMPERING DETECTED !!  |");
		puts("\033[32m.---------------------------.");
		return (1);
	}

	n = (buff[3] ^ 0x1337) + 0x5eeded;
	i = 0;
	while (i < size)
	{
		int		xor;
		int		mul;
		int		res;

		if (buff[i] < 32)
			return (1);
		xor = buff[i] ^ n;
        mul = (xor * 0x88233b2b) >> 32;
        res = (((xor - mul) / 2 + mul) >> 10) * 0x1337;
		n += mul - res;
		i++;
	}
	if (serial == n)
		return (0);
	return (1);
}


int main(void)
{
	char			buff[32];		// $esp + 0x2c
	unsigned int	serial;			// $esp + 0x28

	puts("***********************************");
	puts("*\t\tlevel06\t\t  *");
	puts("***********************************");

	printf("-> Enter Login: ");
	fgets(buff, 32, stdin);

	puts("***********************************");
	puts("***** NEW ACCOUNT DETECTED ********");
	puts("***********************************");

	printf("-> Enter Serial: ");
	scanf("%u", &serial);

	if (auth(buff, serial) == 0)
	{
		puts("Authenticated!");
		system("/bin/sh");
		return (0);
	}
	return (1);
}
