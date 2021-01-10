#include "woody.h"

int    Elf_64_integrity(char *path)
{
    void                    *file;
    Elf64_Ehdr              *ehdr64;
    struct stat             s;
    int                     fd;
    unsigned long           size;

    if (stat(path, &s) == -1)
        return (ft_fatal("stat error"));
    if ((fd = open(path, O_RDONLY)) < 0)
        return (ft_fatal("open error"));
    file = mmap(NULL, s.st_size, PROT_READ | PROT_WRITE, MAP_PRIVATE, fd, 0);
    close(fd);
    if (file == MAP_FAILED)
        return (ft_fatal("mmap failed"));
    size = s.st_size;
    ehdr64 = (Elf64_Ehdr *)file;
    if (size < sizeof(Elf64_Ehdr))
        return (ft_fatal("Invalid Elf file"));
    if (ft_memcmp(ehdr64->e_ident, ELFMAG, SELFMAG))
        return (ft_fatal("Not an ELF file "));
    /* if gcc is configured by default it contain -pie, means they are  
        of type ET_DYN (DYNAMIC LIB) but run like normal binary ; gcc -no-pie */
    if (ehdr64->e_type != ET_EXEC && ehdr64->e_type != ET_DYN)
        return (ft_fatal("Not an ELF executable"));
    if (ehdr64->e_machine != EM_X86_64)
        return (ft_fatal("Elf machine type not X86_64"));
    if (ehdr64->e_version != EV_CURRENT)
        return (ft_fatal("Elf version not current"));
    if (ehdr64->e_phoff == 0 || ehdr64->e_phoff != sizeof(Elf64_Ehdr))
        return (ft_fatal("Elf e_phoff not correct"));
    if (ehdr64->e_phentsize * ehdr64->e_phnum + sizeof(Elf64_Ehdr) > size)
        return (ft_fatal("Program header extend past the end of the file"));
    if (ehdr64->e_shoff + ehdr64->e_shentsize * ehdr64->e_shnum > size)
        return (ft_fatal("Program section extend past the end of the file"));
    return (1);
}

uint64_t  get_text_section_off(char *file)
{
    Elf64_Ehdr          *ehdr64;
    Elf64_Shdr          *shdr64;
    char                *cmp;

    ehdr64 = (Elf64_Ehdr *)file;
    shdr64 = (Elf64_Shdr *)(file + ehdr64->e_shoff);
    char *table = file + (shdr64 + ehdr64->e_shstrndx)->sh_offset;
    for (unsigned int i = 0; i < ehdr64->e_shnum; i++)
    {
        cmp = (char *)(table + shdr64->sh_name);
        if (ft_strcmp(cmp, ".text") == 0)
            return ((size_t)shdr64 - (size_t)file);
        shdr64 = (Elf64_Shdr *)((char *)shdr64 + ehdr64->e_shentsize);
    }
    return (0);
}