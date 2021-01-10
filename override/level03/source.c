#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

void    decrypt(int result)
{
    int     len;
    int     index;
    char    str[17];

    memcpy(str, "Q}|u`sfg~sf{}|a3\0", 17);
    len = strlen(str);

    index = 0;
    while (index < len)
    {
        str[index] ^= result;
        index++;
    }
    
    if (memcmp(str, "Congratulations!", 17) == 0)
        system("/bin/sh");
    else
        puts("\nInvalid Password");
}

void    test(int pass, int number)
{
    int     result;
    
    result = number - pass;
    if (result > 21)
        decrypt(rand());
    else
        decrypt(result);
    return;
}

int     main()
{
    int pass;

    srand(time(0));
    
    puts("***********************************");
    puts("*\t\tlevel03\t\t**");
    puts("***********************************");
    
    printf("Password:");
    scanf("%d", &pass);

    test(pass, 322424845);
    return 0;
}

