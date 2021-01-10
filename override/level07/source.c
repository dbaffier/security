#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void    clear_stdin()
{
	char		c;

	c = 0;
	while (1)
	{
		c = getchar();
		if (c == 10 || c == 0xff)
			return ;
	}
}

unsigned int  get_unum()
{
	unsigned int	unum;

	unum = 0;
    fflush(stdout);
    scanf("%u", &unum);
	clear_stdin();
	return (unum);
}

int    store_number(char buff[100])
{
	unsigned int n;		 // $ebp -  0x10
	unsigned int index;  // $ebp - 0xc
	unsigned int index2;

    n = 0;
    index = 0;
	printf(" Number: ");
	n = get_unum();
	printf(" Index: ");
	index = get_unum();

	index2 = ((index * 0xaaaaaaab) >> 32) >> 1;
    index2 += index2 * 2;

	if ((index - index2) == 0 || n >> 24 == 183)
	{
		puts(" *** ERROR! ***");
		puts("   This index is reserved for wil!");
		puts(" *** ERROR! ***");
		return (1);
	}
	buff[index << 2] = n;
	return (0);
}

int    read_number(char buff[100])
{
	unsigned int		index;
	unsigned int		res;

	index = 0;
	printf(" Index: ");
	index = get_unum();
	res = buff[index << 2];
	printf(" Number at data[%u] is %u\n", index, res);
    return (0);
}

int main(int ac, char **av)
{
    char **args;        /* esp+0x1c  */
    char *env;          /* esp+0x18  */
    char buff[100];     /* esp+0x24  */

    int  control;       /* esp+0x1b4 */    
    char input[20];     /* esp+0x1b8 */
                        
    args = av;
    env = getenv("");

    control = 0;
    memset(input, 0, 20);
    memset(buff, 0, 100);

    for (int i = 0; i < ac; i++)
    {
        memset(*args, 0, strlen(*args));
        *args += 4;
    }
    clearenv();

    puts("----------------------------------------------------\n"\
         "  Welcome to wil's crappy number storage service!   \n"\
         "----------------------------------------------------\n"\
         " Commands:                                          \n"\
         "    store - store a number into the data storage    \n"\
         "    read  - read a number from the data storage     \n"\
         "    quit  - exit the program                        \n"\
         "----------------------------------------------------\n"\
         "   wil has reserved some storage :>                 \n"\
         "----------------------------------------------------\n");
    
    while (1)
    {
        printf("Input command: ");
    
        control = 1;
        fgets(input, 20, stdin);
        input[strlen(input) - 1] = '\0';
    
        if (memcmp(input, "store", 5) == 0)
            control = store_number(buff);
        else if (memcmp(input, "read", 4) == 0)
            control = read_number(buff);
        else if (memcmp(input, "quit", 4) == 0)
            break;

        if (control == 0)
            printf(" Completed %s command successfully\n", input);
        else
            printf(" Failed to do %s command\n", input);
        memset(input, 0, 20);
    }
    return 0;
}

