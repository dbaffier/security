#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

/* rdi, rsi, rdx, rcx, r8, r9, rsp... */

void	log_wrapper(FILE *log, char *msg, char *file_name)
{
	char	buff[254];						// $rbp - 0x110

	strcpy(buff, msg);
    snprintf(buff + strlen(buff), 254 - strlen(buff), file_name);
    buff[strcspn(buff, "\n")] = 0;
    fprintf(log, "LOG: %s\n", buff);
    return;
}

int main(int ac, char **av)
{
	unsigned char   c = 255;					// $rbp - 0x71
	int				fd_file = -1;			    // $rbp - 0x78
	FILE			*log;						// $rbp - 0x88
	FILE			*arg;						// $rbp - 0x80
	char			buff[104];					// $rbp - 0x70

	if (ac != 2)
		printf("Usage: %s filename\n", av[0]);
	log = fopen("./backups/.log", "w");
	if (log == NULL)
	{
		printf("ERROR: Failed to open %s\n", "./backups/.log");
		exit(1);
	}
	log_wrapper(log, "Starting back up: ", av[1]);
	arg = fopen(av[1], "r");
	if (arg == NULL)
	{
		printf("ERROR: Failed to open %s\n", av[1]);
		exit(1);
	}
	strcpy(buff, "./backups/");
	strncat(buff, av[1], 99 - strlen(buff));
	fd_file = open(buff, 193, 432);
	if (fd_file < 0)
	{
		printf("ERROR: Failed to open %s%s\n", "./backups/", av[1]);
		exit(1);
	}
	while((c = fgetc(arg)) != 255)
		write(fd_file, c, 1);
	log_wrapper(log, "Finished back up ", av[1]);
	fclose(arg);
	close(fd_file);

	return (0);
}
