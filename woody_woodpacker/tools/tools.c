

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaffier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/18 17:17:07 by dbaffier          #+#    #+#             */
/*   Updated: 2020/01/18 17:19:07 by dbaffier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "woody.h"

void		fput(char *file, void *ptr, int len, int offset, int seek)
{
	int		fd;

    fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 00755);
	if (fd < 0)
		ft_err(NULL, NULL);
	if (offset > 0)
		lseek(fd, seek, offset);
	write(fd, ptr, len);
	close(fd);
}

void		*ft_memset(void *b, int c, size_t len)
{
	char	*s;
	size_t	i;

	s = (char *)b;
	i = 0;
	while (i < len)
		s[i++] = c;
	return ((void *)s);
}

void	ft_strncpy(char *dst, const char *src, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n && src[i])
	{
		dst[i] = src[i];
		i++;
	}
	while (i < n)
	{
		dst[i] = 0;
		i++;
	}
}

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char	*src2;
	char	*dst2;

	src2 = (char *)src;
	dst2 = (char *)dst;
	if (n == 0 || dst == src)
		return ((void *)dst);
	while (n != 0)
	{
		*dst2++ = *src2++;
		n--;
	}
	return ((void *)dst);
}

char		*ft_strrchr(const char *s, int c)
{
	char	*p;
	int		locate;

	if (s == NULL)
		return (NULL);
	p = (char *)s;
	locate = 0;
	while (p && *p != '\0')
	{
		if (*p == c)
			locate = p - s;
		p++;
	}
	return ((char *)s + locate);
}

size_t		ft_strcmp(char *src, char *cmp)
{
	size_t		i;
	size_t		j;

	i = 0;
	j = 0;
	if (!src || !cmp)
		return (0);
	while (src[i] && cmp[i] && src[i] == cmp[j])
	{
		i++;
		j++;
	}
	if (src[i] == cmp[j])
		return (0);
	return (1);
}

size_t		ft_strlen(const char *str)
{
	int		i;
	if (str == NULL)
		return (0);
	i = 0;
	while (str[i])
	{
		if ((unsigned int)str[i + 1] == 0x00)
			return (i + 1);
		if ((unsigned int)str[i + 2] == 0x00)
			return (i + 2);
		if ((unsigned int)str[i + 3] == 0x00)
			return (i + 3);
		i += 4;
	}
	return (i);
}

int			ft_usage(void)
{
	printf("woody_woodpacker: <flags> <file>\n");
	return (0);
}
