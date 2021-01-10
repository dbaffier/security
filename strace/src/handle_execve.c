#include "ft_strace.h"

void    handle_execve(pid_t child, t_print *print)
{
    (void)child;
    if (print->flag == 1)
    {
        dprintf(2, "\"%s\", [", print->target);
        for (int i = 0; print->args[i]; i++)
        {
            if (print->args[i + 1])
                dprintf(2, "\"%s\", ", print->args[i]);
            else
                dprintf(2, "\"%s\"", print->args[i]);
        }
        dprintf(2, "], %p /* %d vars */", print->env_addr, print->env_count);
        free(print->target);
        print->env_addr = 0;
        print->args = 0;
    }
}