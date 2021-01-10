#include <string.h>
#include <stdio.h>
#include <stdlib.h>

/* RDI, RSI, RDX, RCX, R8, R9, RSP... */

int main(int ac, char **av)
{
	FILE    *file;               /* RBP-0x8   */
	size_t	size;                /* RBP-0xc   */

	char    username[100];       /* RBP-0x70  */
	char    real_pass[41];       /* RBP-0xa0  */
	char    input_pass[100];     /* RBP-0x110 */

	memset(username, 0, 100);
	memset(real_pass, 0, 41); 
    memset(input_pass, 0, 100); 
	size = 0;

	file = fopen("/home/users/level03/.pass", "r");
	if (file == 0)
	{
		fwrite("ERROR: failed to open password file\n", 1, 36, stderr);
		exit(1);
	}

	size = fread(real_pass, 1, 41, file);
	real_pass[strcspn(real_pass, "\n")] = 0;
	if (size != 41)
	{
		fwrite("Error: failed to read password file\n", 1, 36, stderr);
		return (1);
	}
	fclose(file);

    /**/

	puts("===== [ Secure Access System v1.0 ] =====");
	puts("/***************************************\\");
	puts("| You must login to access this system. |");
	puts("\\**************************************/");
	
    printf("--[ Username: ");
	fgets(username, 100, stdin);
	username[strcspn(username, "\n")] = 0;

	printf("--[ Password: ");
	fgets(input_pass, 100, stdin);
	input_pass[strcspn(input_pass, "\n")] = 0;

	puts("*****************************************");
	
    /**/

    if (strncmp(input_pass, real_pass, 41) == 0)
	{
		printf("Greetings, %s!\n", username);
		system("/bin/sh");
		return (0);
	}
	
    printf(username);
	puts(" does not have access!");
	exit (1);
}
