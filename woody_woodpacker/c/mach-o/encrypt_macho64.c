#include "woody.h"

void text_infect(void);
extern uint32_t infect_size;
static void patch_macho_header(t_packer *pack, struct section_64 *sectext, struct segment_command_64 *lastseg);
// static void copy_infection(int fd, t_packer *pack, uint64_t *old_entryoff, uint64_t textoff, uint64_t textsize);
// static void copy_infection(int fd, t_packer *pack, uint64_t *old_entryoff, uint32_t textoff, uint64_t textsize);

void encrypt_macho64(t_packer *pack)
{
    struct section_64 *sectext = (struct section_64 *)((char *)pack->map + find_sectext(pack->map));
    struct segment_command_64 *lastseg = (struct segment_command_64 *)
                    (pack->map + file_offset_lsegment(pack->map, LC_SEGMENT_64));
    
    RC4(pack->key, (unsigned char *)pack->map + sectext->offset, sectext->size);
    patch_macho64_header(pack->map);
    patch_macho_header(pack, sectext, lastseg);
}

static void patch_macho_header(t_packer *pack, struct section_64 *sectext, struct segment_command_64 *lastseg)
{
    uint64_t new_entryoff = last_seg_offset_end(pack->map, LC_SEGMENT_64);
    uint64_t old_entryoff = patch_entryoff(pack->map, new_entryoff);
    uint64_t offset_write = file_offset_end_lsegment(pack->map, LC_SEGMENT_64);


    /* Make TEXT writable */
    if (!(find_segment(pack->map, SEG_TEXT)->initprot & VM_PROT_WRITE))
        find_segment(pack->map, SEG_TEXT)->initprot |= VM_PROT_WRITE;
        
    int fd = open("woody", O_WRONLY | O_CREAT | O_TRUNC, 00755);
    if (fd < 0)
        ft_err(NULL, pack);

    /* Write to last LC_SEGMENT_64 segment offset */
    write(fd, pack->map, offset_write);

    /* Setup new segment and is associated section */
    struct segment_command_64 new_sg = create_segment("__DB", LC_SEGMENT_64, 0x1 | 0x2 | 0x4);
    struct section_64 new_s = create_section("__db");

    size_t isize = infect_size + sizeof(sectext->size) + sizeof(uint64_t) + 14 + sizeof(old_entryoff) + 8;

    new_sg.vmaddr = last_seg_vmoffset_end(pack->map, LC_SEGMENT_64);
    while (new_sg.vmsize < isize)
        new_sg.vmsize += getpagesize();
    new_sg.fileoff = last_seg_offset_end(pack->map, LC_SEGMENT_64);
    new_sg.filesize = isize;
    /* Write our new segment */
    write(fd, &new_sg, sizeof(new_sg));
    ft_strncpy(new_s.segname, "__DB", sizeof(new_s.segname));
    new_s.addr = new_sg.vmaddr;
    new_s.size = isize;
    new_s.offset = new_sg.fileoff;
    new_s.align = sectext->align;
    new_s.flags = sectext->flags;
    /* Write our new section */
    write(fd, &new_s, sizeof(new_s));
    /* Write from current index to sectext */
    write(fd, pack->map + offset_write, (sectext->offset - new_sg.cmdsize) - offset_write);
    /* Write from current index to end */
    write(fd, pack->map + sectext->offset, pack->map_size - sectext->offset - 1);
    
    /* pad to 0 lastsegment (VM + size ), since we're not at the end of the file anymore */
    for (uint32_t i = lastseg->vmsize - lastseg->filesize; i > 0; i--)
        write(fd, "\0", 1);
    // copy_infection(fd, pack, &old_entryoff, sectext->offset - new_entryoff, sectext->size);
    write(fd, &text_infect, infect_size);

    uint64_t textoff = sectext->offset - new_entryoff;
    printf("%llu\n", textoff);

    printf("%llu\n", pack->marksize);
    write(fd, &textoff, sizeof(textoff));
    write(fd, &sectext->size, sizeof(sectext->size));
    write(fd, &old_entryoff, sizeof(old_entryoff));
    // write(fd, &pack->marksize, sizeof(pack->marksize));
    write(fd, pack->mark, pack->marksize);
    write(fd, pack->key, 8);
    close(fd);
}

// static void copy_infection(int fd, t_packer *pack, uint64_t *old_entryoff, uint32_t textoff, uint64_t textsize)
// {
//     write(fd, &text_infect, infect_size);

//     write(fd, &textoff, sizeof(textoff));

//     write(fd, &textsize, sizeof(textsize));
//     write(fd, old_entryoff, sizeof(old_entryoff));
//     printf("%zu\n", sizeof(pack->marksize));
//     write(fd, &pack->marksize, sizeof(pack->marksize));
//     write(fd, pack->mark, pack->marksize);
//     write(fd, pack->key, 8);

// }