/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaffier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/18 16:51:57 by dbaffier          #+#    #+#             */
/*   Updated: 2020/01/19 18:49:28 by dbaffier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "woody.h"


int     file_integrity(t_packer *pack, char *path)
{
    char    buff[1024];
    int     i;
    int     ret;

    if ((pack->fd = open(path, O_RDONLY)) == -1)
        return (ft_err(NULL, pack));
    if ((pack->map_size = lseek(pack->fd, 1, SEEK_END)) == -1)
        return (ft_err(NULL, pack));
    pack->map = mmap(NULL, pack->map_size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    if (pack->map == MAP_FAILED)
        return (ft_err(NULL, pack));
    if (lseek(pack->fd, 0, SEEK_SET) == -1)
        return (ft_err(NULL, pack));
    i = 0;
    while ((ret = read(pack->fd, &buff, sizeof(buff))) > 0)
    {
        ft_memcpy(pack->map + i, &buff, ret);
        i += ret;
    }
    if (ret)
        return (ft_err(NULL, pack));
    if (close(pack->fd) == -1)
        perror("close()");
    pack->fd = 0;
    return (0);
}