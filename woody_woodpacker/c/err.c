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