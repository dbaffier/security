#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct  s_message
{
        char    content[140];
        char    username[40];
        int     size_content;

}               t_message;

void    secret_backdoor()
{
    char	buff[128];
	
    fgets(buff, 128, stdin);
    system(buff);
}

void	set_msg(t_message *new)
{
    t_message   *msg;
    char	    buff[1024];

    msg = new;
    memset(buff, 0, 1024);

    puts(">: Msg @Unix-Dude");
    printf(">>: ");
	
    fgets(buff, 1024, stdin);
    strncpy(msg->content, buff, msg->size_content);
}

void	set_username(t_message *new) 
{
    t_message   *msg;
    char	    username[128]; 
    int         index; 

    msg = new;
    memset(username, 0, 128);
    puts(">: Enter your username");
    printf(">>: ");
    fgets(username, 128, stdin);
    index = 0;
    while (index <= 40 && username[index] != 0) 
    {
        msg->username[index] = username[index];
        index++;
    }
    printf(">: Welcome, %s", msg->username);
}

void	handle_msg()
{
    t_message new;

    memset(new.username, 0, 40);
    new.size_content = 140;
    set_username(&new);
    set_msg(&new);
    puts(">: Msg sent!");
}

int main(void)
{
    puts("--------------------------------------------\n"\
         "|   ~Welcome to l33t-m$n ~    v1337        |\n"\
         "--------------------------------------------\n");
    handle_msg();
    return (0);
}
