#include "woody.h"

extern uint32_t infect_size;
void text_infect(void);


void        encrypt_elf64(t_packer *pack)
{
    Elf64_Phdr      *phdr64;
    Elf64_Ehdr      *ehdr64;
    Elf64_Shdr      *sectext;
    int             plen;
    int             vlen;
    int             i;
    int             evaddr;
    int             padding = 0;
    size_t          offset = 0;
    uint64_t        old_entry;
    uint64_t        stext_off;

    ehdr64 = (Elf64_Ehdr *)pack->map;
    sectext = (Elf64_Shdr *)(pack->map + get_text_section_off(pack->map));
    phdr64 = (Elf64_Phdr *)((char *)pack->map + ehdr64->e_phoff);
    if (!pack->flags.m)
    {
    	ft_strncpy(pack->mark, "....WOODY....", 255);
	    pack->marksize = ft_strlen(pack->mark) + 1;
    }
    #ifdef DEBUG
        printf("------TEXT SECTION-----\n");
        printf("\t addr       offset       size \n");
        printf("\t %#lx     %#lx         %#lx\n", sectext->sh_addr, sectext->sh_offset, sectext->sh_size);
        printf("------PROGRAM HEADER-----\n");
        printf("\t offset : %lx\n", phdr64->p_offset);
    #endif
   
    /*
     ** All of these are needed by the infection
     ** The 16 last bytes are for the key.
    */
    vlen = infect_size 
        + sizeof(stext_off)
        + sizeof(sectext->sh_size)
        + sizeof(old_entry) 
        + sizeof(pack->marksize)
        + pack->marksize + 16;
    while (padding < vlen)
        padding += getpagesize();
    #ifdef DEBUG
        printf("parasite len : %x\n", vlen);
        printf("Padding len : %x\n", padding);
    #endif

    /* Encryption */
    #ifdef DEBUG
        printf("Encryption starting at %lx for size of %lx\n", sectext->sh_offset, sectext->sh_size);
    #endif
    RC4(pack->key, (unsigned char *)((char *)pack->map + sectext->sh_offset), sectext->sh_size);

    for (i = 0; i < ehdr64->e_phnum; i++)
    {
        if (phdr64->p_offset >= offset && offset != 0)
            phdr64->p_offset += padding;
        else if (phdr64->p_type == PT_LOAD && phdr64->p_flags & PF_X)
        {
            if (phdr64->p_filesz != phdr64->p_memsz) /* need to be equal as by manuel */
                ft_fatal("Error align");
            evaddr = phdr64->p_vaddr + phdr64->p_filesz;
            plen = (getpagesize() - (evaddr & (getpagesize() - 1)));
            if (plen < vlen)
                ft_fatal("parasite too large\n");
            old_entry = (phdr64->p_vaddr + phdr64->p_memsz - ehdr64->e_entry) * (-1);
            ehdr64->e_entry = phdr64->p_vaddr + phdr64->p_memsz;
            offset = phdr64->p_offset + phdr64->p_filesz;
            #ifdef DEBUG
                printf("old entrypoint : %lx\n", old_entry);
                printf("new entrypoint : %lx\n", ehdr64->e_entry);
                printf("Parasite file offset : %li\n", offset);
            #endif
            /* virus entry - sh_addr = offset */
            stext_off = (ehdr64->e_entry - sectext->sh_addr) * (-1);
            phdr64->p_filesz += vlen;
            phdr64->p_memsz += vlen;
            phdr64->p_flags = PF_R | PF_W | PF_X; /* decryption need to be writable */
        }
        ++phdr64;
    }
    if (offset == 0)
        ft_fatal("No text segment?");
    i = 0;
    for (Elf64_Shdr *p = (Elf64_Shdr *)((char *)pack->map + ehdr64->e_shoff); i < ehdr64->e_shnum; i++)
    {
        if (p->sh_offset >= offset)
            p->sh_offset += padding;
        // else if (p->sh_addr + p->sh_size == (long unsigned int)evaddr)
            // p->sh_size += vlen; /* Increasing  section text by virus size */
        ++p;
    }
    if (ehdr64->e_shoff >= offset)
        ehdr64->e_shoff += padding;

    int fd = open("woody", O_WRONLY | O_CREAT | O_TRUNC, 00755);
    if (fd < 0)
        ft_err(NULL, pack);
    #ifdef DEBUG
        printf("Offset write  : %lx\n", offset);
        printf("Sectext offset : %lx\n", stext_off);
        printf("Sectext size : %lx\n", sectext->sh_size);
        printf("Old entry : %x\n", *(unsigned int *)&old_entry);
    #endif
    write(fd, (char *)pack->map, offset);
    write(fd, &text_infect, infect_size);
    write(fd, &stext_off, sizeof(stext_off));
    write(fd, &sectext->sh_size, sizeof(sectext->sh_size));
    write(fd, &old_entry, sizeof(old_entry));
    write(fd, &pack->marksize, sizeof(pack->marksize));
    write(fd, pack->mark, pack->marksize - 1);
    write(fd, "\n", 1);
    write(fd, pack->key, 16);
    while (padding-- > vlen)
        write(fd, "\0", 1);
    write(fd, (char *)pack->map + offset, pack->map_size - offset - 1);
    close(fd);
}