/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   woody.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaffier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/18 17:20:52 by dbaffier          #+#    #+#             */
/*   Updated: 2020/01/18 18:11:10 by dbaffier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOODY_H
# define WOODY_H

#define EXIT_ERR 1

#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdint.h>

#ifdef __APPLE__
 #include <mach-o/loader.h>
#endif

#ifdef __linux__
 #include <elf.h>
#endif

typedef struct s_flags
{
	unsigned int m : 1; /* -m for msg */
} t_flags;

/*
** Packer struct
*/

typedef struct s_packer
{
	int 		fd;
	void 		*map;
	ssize_t 	map_size;
	char 		*progname;
	char 		*key;
	char 		mark[256];
	uint64_t 	marksize;
	t_flags 	flags;
} t_packer;

/* MACHO HELPER  macho.c */
#ifdef __APPLE__
struct segment_command_64
							create_segment(char segname[16], uint32_t cmd, vm_prot_t protection);
struct section_64 			create_section(char sectname[16]);


struct segment_command_64 	*find_segment(char *file, char *cmp);
uint32_t					find_sectext(char *file);

size_t 		file_offset_lsegment(char *file, uint32_t cmp);
size_t 		file_offset_end_lsegment(char *file, uint32_t cmp);
uint64_t    last_seg_offset_end(char *file, uint32_t cmp);
uint64_t 	last_seg_vmoffset_end(char *file, uint32_t cmp);
uint64_t 	entry_offset(char *file);
uint64_t    patch_entryoff(char *file, uint64_t new);
void 		patch_macho64_header(char *file);
int			is_Macho(uint32_t magic);
int			Macho_64(uint32_t magic);
int    		Mach_O_integrity(char *path);

/* MACHO */
void is_macho(t_packer *packer);
void encrypt_macho64(t_packer *pack);
#endif

#ifdef __linux__
int    		Elf_64_integrity(char *path);
uint64_t  	get_text_section_off(char *file);



void        encrypt_elf64(t_packer *pack);

#endif

/* ENCRYPTION */
void RC4(char *key, unsigned char *plaintext, uint32_t size);
void generate_key(t_packer *pack);

/* TOOLS */
void		fput(char *file, void *ptr, int len, int offset, int seek);
void		*ft_memset(void *b, int c, size_t len);
void 		*ft_memcpy(void *dst, const void *src, size_t n);
char 		*ft_strrchr(const char *s, int c);
void 		ft_strncpy(char *dst, const char *src, size_t n);
size_t 		ft_strlen(const char *str);
size_t 		ft_strcmp(char *src, char *cmp);
int			ft_memcmp(const void *s1, const void *s2, size_t n);


/* ERROR */
int file_integrity(t_packer *pack, char *path);
int parse_flag(char **av, int i, t_packer *pack);
int ft_err(char *s, t_packer *pack);
int ft_usage(void);
int ft_fatal(char *s);

#endif
