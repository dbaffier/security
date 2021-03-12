#include <unistd.h>
#include <string.h>

int main(void)
{
	char	buff[8];

	read(0, buff, 8);
	if (strcmp(buff, "AAAAAAAA") == 0)
		printf("Ok!\n");
	else
		printf("No!\n");
}
