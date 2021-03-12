



// 65 - 0 + 20 ==  85 != 65
// 65 - 1 + 20 ==  84

// 65 - 0 + 20  !=  input[0]
// 66 - 1 + 20  !=	input[1]


// 65 - 28 + 20 != 65
// 


int main(int ac, char **av)
{
	int len = 32;

	if (len == 1)
	{
		return  (0x1337);
	}
	else
	{
		int	i = 0;
		while (i != len - 1)
		{
			if (((input[i] -  i) + 0x14) != input2[i])
				return (0x1337);
			i++;
		}
		printf("Good\n");
	}
	printf("No\n");
}
