#include "woody.h"


/*
** 
*/

int    Mach_O_integrity(char *path)
{
    void                    *file;
    struct stat             stat;
    struct mach_header_64   mh64;
    struct load_command     *lc;


    stat = stat(path, &stat);
    if (stat == -1)
        return (0);
    file = mmap(NULL, stat.st_size PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    if (file == MAP_FAILED)
        return (0);
    if (!is_Macho(*(unsigned int *)file))
        return (0);
    mh64 = (struct mach_header_64 *)file;
    lc = (struct load_command *)(fiile + sizeof(struct mach_header_64));
    if (mh64->sizeofcmds + sizeof(struct mach_header_64) > stat.st_size)
        return (0);
}

int		is_Macho(uint32_t magic)
{
	return (magic == MH_MAGIC || magic == MH_CIGAM ||
			magic == MH_MAGIC_64 || magic == MH_CIGAM_64);
}	

int		Macho_64(uint32_t magic)
{
	return (magic == MH_MAGIC_64 || magic == MH_CIGAM_64);
}

/*
** Return file offset to last cmp
*/

size_t file_offset_lsegment(char *file, uint32_t cmp)
{
    struct mach_header_64 *mh64;
    struct load_command *lc;
    struct segment_command_64 *sc;

    mh64 = (struct mach_header_64 *)file;
    lc = (struct load_command *)(file + sizeof(struct mach_header_64));
    for (size_t i = 0; i < mh64->ncmds; i++)
    {
        if (lc->cmd == cmp)
            sc = (struct segment_command_64 *)lc;
        lc = (struct load_command *)((char *)lc + lc->cmdsize);
    }
    return ((size_t)sc - (size_t)file);
}

/*
** Return offset to the end of last LC_SEGMENT_64 from *file
*/

size_t file_offset_end_lsegment(char *file, uint32_t cmp)
{
    struct mach_header_64 *mh64;
    struct load_command *lc;
    struct segment_command_64 *sc;

    mh64 = (struct mach_header_64 *)file;
    lc = (struct load_command *)(file + sizeof(struct mach_header_64));
    for (size_t i = 0; i < mh64->ncmds; i++)
    {
        if (lc->cmd == cmp)
            sc = (struct segment_command_64 *)lc;
        lc = (struct load_command *)((char *)lc + lc->cmdsize);
    }
    return ((((size_t)sc + (size_t)sc->cmdsize)) - (size_t)file);
}

/*
** Return entry offset (__TEXT of main)
** Work only for MH_EXECUTE
*/

uint64_t entry_offset(char *file)
{
    struct mach_header_64 *mh64;
    struct load_command *lc;

    mh64 = (struct mach_header_64 *)file;
    lc = (struct load_command *)(file + sizeof(struct mach_header_64));
    for (size_t i = 0; i < mh64->ncmds; i++)
    {
        if (lc->cmd == LC_MAIN)
            return (((struct entry_point_command *)lc)->entryoff);
        lc = (struct load_command *)((char *)lc + lc->cmdsize);
    }
    ft_fatal("entryoff not found");
    return (0);
}

/*
** Return file data offset to the end of lc(segment)
** -> new entryoff
*/

uint64_t    last_seg_offset_end(char *file, uint32_t cmp)
{
    struct mach_header_64       *mh64;
    struct load_command         *lc;
    struct segment_command_64   *sc;

    mh64 = (struct mach_header_64 *)file;
    lc = (struct load_command *)(file + sizeof(struct mach_header_64));
    for (size_t i = 0; i < mh64->ncmds; i++)
    {
        if (lc->cmd == cmp)
            sc = (struct segment_command_64 *)lc;
        lc = (struct load_command *)((char *)lc + lc->cmdsize);
    }
    return (sc->fileoff + sc->vmsize);
}

/*
** Return vmaddr offset to the end of lc(segment)
*/

uint64_t last_seg_vmoffset_end(char *file, uint32_t cmp)
{
    struct mach_header_64       *mh64;
    struct load_command         *lc;
    struct segment_command_64   *sc;

    mh64 = (struct mach_header_64 *)file;
    lc = (struct load_command *)(file + sizeof(struct mach_header_64));
    for (size_t i = 0; i < mh64->ncmds; i++)
    {
        if (lc->cmd == cmp)
            sc = (struct segment_command_64 *)lc;
        lc = (struct load_command *)((char *)lc + lc->cmdsize);
    }
    return (sc->vmaddr + sc->vmsize);
}

/*
** Patch entryoff
** Return old entryoff - size of new entry (since file will be bigger)
*/

uint64_t        patch_entryoff(char *file, uint64_t new)
{
    struct mach_header_64   *mh64;
    struct load_command     *lc;
    uint64_t                old;

    mh64 = (struct mach_header_64 *)file;
    lc = (struct load_command *)(file + sizeof(struct mach_header_64));
    old = entry_offset(file);
    for (size_t i = 0; i < mh64->ncmds; i++)
    {
        if (lc->cmd == LC_MAIN)
            ((struct entry_point_command *)lc)->entryoff = new;
        lc = (struct load_command *)((char *)lc + lc->cmdsize);
    }
    return (old - new);
}

/*
** Increase segment and size by 1
** Disable ASLR
*/

void patch_macho64_header(char *file)
{
    struct mach_header_64 *mh64;

    mh64 = (struct mach_header_64 *)file;

    mh64->ncmds += 1;
    mh64->sizeofcmds += (sizeof(struct segment_command_64) + sizeof(struct section_64));
    /* disable ASLR (random space address) */
    mh64->filetype &= ~MH_PIE;
}

/*
** Find segment by cmp
*/

struct segment_command_64 *find_segment(char *file, char *cmp)
{
    struct mach_header_64   *mh64;
    struct load_command     *lc;

    mh64 = (struct mach_header_64 *)file;
    lc = (struct load_command *)(file + sizeof(struct mach_header_64));
    for (size_t i = 0; i < mh64->ncmds; i++)
    {
        if (lc->cmd == LC_SEGMENT_64)
        {
            if (ft_strcmp(((struct segment_command_64 *)lc)->segname, cmp) == 0)
                return ((struct segment_command_64 *)lc);
        }
        lc = (struct load_command *)((char *)lc + lc->cmdsize);
    }
    return (NULL);
}

/*
** Return file offset of section __text
*/

uint32_t    find_sectext(char *file)
{
    struct mach_header_64   *mh64;
    struct load_command     *lc;
    struct section_64       *section64;


    mh64 = (struct mach_header_64 *)file;
    lc = (struct load_command *)(file + sizeof(struct mach_header_64));
    for (size_t i = 0; i < mh64->ncmds; i++)
    {
        if (lc->cmd == LC_SEGMENT_64)
        {
            if (ft_strcmp(((struct segment_command_64 *)lc)->segname, SEG_TEXT) == 0)
            {
                section64 = (struct section_64 *)((char *)lc + sizeof(struct segment_command_64));
                for (size_t j = 0; j < ((struct segment_command_64 *)lc)->nsects; j++)
                {
                    if (ft_strcmp((section64 + j)->sectname, SECT_TEXT) == 0)
                        return ((size_t)(section64 + j) - (size_t)file);

                }
            }
        }
        lc = (struct load_command *)((char *)lc + lc->cmdsize);
    }
    return (0);
}

/*
** Create new segment
** By default contain 1 section.
** By default protection are applied to both maxprot and initprot
*/

struct segment_command_64 create_segment(char segname[16], uint32_t cmd, vm_prot_t protection)
{
    struct segment_command_64       segment;

    segment.cmd = cmd;
    ft_strncpy(segment.segname, segname, 16);
    segment.cmdsize = sizeof(struct segment_command_64) + sizeof(struct section_64);
    segment.vmaddr = 0;
    segment.vmsize = 0;
    segment.fileoff = 0;
    segment.filesize = 0;
    segment.maxprot = protection;
    segment.initprot = protection;
    segment.nsects = 1;
    segment.flags = 0;

    return (segment);
}

/*
** Create new section
*/

struct section_64 create_section(char sectname[16])
{
    struct section_64 section;

    ft_memset(&section, 0, sizeof(struct section_64));
    ft_strncpy(section.sectname, sectname, 16);
    
    return (section);
}