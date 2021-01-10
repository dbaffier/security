#include <stdio.h>
#include <strings.h>
#include <string.h>

char    a_user_name[256];

int     verify_user_name(void)
{
    puts("verifying username....\n");
    return (memcmp(a_user_name, "dat_wil", 7));
}

int     verify_user_pass(char buffer[64])
{
    return (memcmp(buffer, "admin", 5));
}


int     main ()
{
    char buffer[64];
    int  result;    

    bzero(buffer, 64);
    result = 0;

    puts("********* ADMIN LOGIN PROMPT *********");

    printf("Enter Username: ");
    fgets(a_user_name, 256, stdin);
    result = verify_user_name();
    if (result != 0)
    {
        puts("nope, incorrect username...\n");
        return 1;
    }

    puts("Enter Password: ");
    fgets(buffer, 100, stdin);
    result = verify_user_pass(buffer);
    if (result != 0)
    {
        if (result == 0)
            return 0;
    }
    puts("nope, incorrect password...\n")
    return 1;
}
