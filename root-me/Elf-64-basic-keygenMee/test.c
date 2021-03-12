#include <stdio.h>
#include <fcntl.h>

int main(void)
{
	char	tab[] = "root-me.org";

	int	fd = open(".m.key", O_WRONLY);
	for (int i = 0; i < 11;  i++)
	{
		unsigned char	c;
		c = tab[i] - i + 20;
		write(fd, &c, 1);
		printf("%x ", c);
	}
}
