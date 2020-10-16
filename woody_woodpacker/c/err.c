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

int     ft_err(char *s, t_packer *pack)
{
    (void)pack;
    fprintf(stderr, "%s: ", pack->progname);
    if (!s)
        perror(s);
    else
        fprintf(stderr, "%s\n", s);
    exit(1);
}

int     ft_fatal(char *s)
{
    fprintf(stderr, "%s\n", s);
    exit(1);
}

// int			ft_fatal(char *str, t_env *e)
// {
// 	ft_fprintf(stderr, "%s: ", e->progname);
// 	if (!str)
// 		perror(str);
// 	else
// 		ft_fprintf(stderr, "%s\n", str);
// 	if (e->fd > 0)
// 		close(e->fd);
// 	if (e->file != MAP_FAILED)
// 		munmap(e->file, e->file_size);
// 	remove(OUTPUT_FILENAME);
// 	exit(1);