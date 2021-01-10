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

void    generate_key(t_packer *pack)
{
    int             fd;
    char            key[16];

    fd = open("/dev/urandom", O_RDONLY);
    if (!fd)
        ft_err("Cannot generate KEY", pack);
    read(fd, &key, 16);
    for (size_t i = 0; i < sizeof(key); i++)
        key[i] = ((key[i] / 256.0 * (rand() % 26)) + 65);
    key[15] = 0;
    pack->key = malloc(sizeof(char) * 16);
    if (!pack->key)
        ft_err("Malloc error", pack);
    for (int i = 0; i < 16 + 1; i++)
        pack->key[i] = key[i];
    printf("key_value : [%s]\n", pack->key);
    close(fd);
}

int main(int ac, char **av)
{
	t_packer	pack;
	int			i;

	ft_memset(&pack, 0, sizeof(t_packer));
	pack.progname = ft_strrchr(av[0], '/') + 1;
	i = parse_flag(av, 1, &pack);
	if (!av || !av[i] || ac == 1)
		return (ft_usage());
	file_integrity(&pack, av[i]);
    if (!pack.key)
        generate_key(&pack);
#ifdef __linux__
    if (Elf_64_integrity(av[i]) == 0)
        return (0);
    encrypt_elf64(&pack);
#endif
#ifdef __APPLE__
    if (Mach_O_integrity(av[i]) == 0)
        return (0);
	encrypt_macho64(&pack);
#endif
    free(pack.key);
    munmap(pack.map, pack.map_size);
	return (0);
}
