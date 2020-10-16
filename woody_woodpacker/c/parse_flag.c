#include "woody.h"

int     parse_flag(char **av, int i, t_packer *pack)
{
    t_flags     flags;

    ft_memset(&flags, 0, sizeof(t_flags));
    while (av[i] && av[i][0] == '-')
    {
        if (!ft_strcmp(av[i], "--virus") || !ft_strcmp(av[i], "-v"))
            flags.v = 1;
        else if (!ft_strcmp(av[i], "--key") || !ft_strcmp(av[i], "-k"))
        {
            if (!av[i + 1])
                ft_err("You should specify a KEY", pack);
            flags.k = 1;
            i++;
            pack->key = av[i];
        }
        else
            ft_err("Unknown flag", pack);       
        i++;
    }
    pack->flags = &flags;
    return (i);
}