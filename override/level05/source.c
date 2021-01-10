#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    char buff[100];     /*esp+0x28*/
    int  index;         /*esp+0x8c*/

    fgets(buff, 100, stdin);
    index = 0;
    
    while (strlen(buff) > index)
    {
        if (buff[index] > 64 && buff[index] <= 90)
            buff[index] ^= 32;
        index++;
    }
    printf(buff);
    exit (0);
}

