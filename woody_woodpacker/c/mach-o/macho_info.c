#include "woody.h"

static int		check_macho(uint32_t magic)
{
	return (magic == MH_MAGIC || magic == MH_CIGAM ||
			magic == MH_MAGIC_64 || magic == MH_CIGAM_64);
}	

static int		is_64(uint32_t magic)
{
	return (magic == MH_MAGIC_64 || magic == MH_CIGAM_64);
}

/*
** File integrity of mach-O format.
** Check format type and if executable.
*/

void    is_macho(t_packer *packer)
{
    uint32_t			    magic;
    struct mach_header      *mh;
    struct mach_header_64   *mh64;

    magic = *(unsigned int *)packer->map;
    mh64 = NULL;
    if (!check_macho(magic))
        ft_err("This is not a macho-o file", packer);
    if (is_64(magic))
    {
        mh64 = (struct mach_header_64 *)packer->map;
        if (mh64->filetype != MH_EXECUTE)
            ft_err("File is not an executable (x64)", packer);
    }
    else
    {
        mh = (struct mach_header *)packer->map;
        if (mh->filetype != MH_EXECUTE)
            ft_err("File is not an executable (x32)", packer);
    }
}