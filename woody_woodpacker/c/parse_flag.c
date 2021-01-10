#include "woody.h"

int     parse_flag(char **av, int i, t_packer *pack)
{
    t_flags     flags;

    ft_memset(&flags, 0, sizeof(t_flags));
    while (av && av[i] && av[i][0] == '-')
    {
        if (!ft_strcmp(av[i], "-m"))
        {
            if (!av[i + 1])
                ft_err("You should specify a MSG (255 length max)", pack);
            pack->flags.m |= 1;
            i++;
            ft_strncpy(pack->mark, av[i], 255);
            pack->marksize = ft_strlen(pack->mark) + 1;
        }
        else
            ft_err("Unknown flag", pack);       
        i++;
    }
    return (i);
}