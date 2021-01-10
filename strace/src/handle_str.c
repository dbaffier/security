#include "ft_strace.h"


void     write_str(char *str, int rax)
{
    int     read;

    read = 0;
    dprintf(2, "\"");
    while (read < rax && read < 32)
    {
        if (str[read] == '\n')
            dprintf(2, "\\n");
        else if (str[read] == '\t')
            dprintf(2, "\\t");
        else if (str[read] == '\r')
            dprintf(2, "\\r");
        else if (str[read] == '\v')
            dprintf(2, "\\v");
        else if (isprint(str[read]))
            dprintf(2, "%c", str[read]);
        else
            dprintf(2, "\\%o", (str[read] & 0xFF));
        read++;
    }
    dprintf(2, "\"");
    if (read < rax)
        dprintf(2, "...");
}

char    *read_string(pid_t child, unsigned long addr, int *len)
{
    char                *buff;
    int                 read;
    unsigned long       n;
    int                 allocated;

    allocated = 4096;
    if ((buff = malloc(4096)) == NULL)
        return (NULL);
    read = 0;
    while (1)
    {
        if ((int)(read + sizeof(n)) > allocated)
        {
            allocated *= 2;
            buff = realloc(buff, allocated);
        }
        n = ptrace(PTRACE_PEEKDATA, child, addr + read);
        if (errno != 0)
        {
            buff[read] = 0;
            break ;
        }
        memcpy(buff + read, &n, sizeof(n));
        read += sizeof(n);
    }
    *len = read;
    return (buff);
}


char     *read_chars(pid_t child, unsigned long long int addr, int rax)
{
    char            *str;
    int             allocated;
    int             read;
    unsigned long   tmp;

    read = 0;
    allocated = 4096;
    if (!(str = malloc(4096)))
        return (NULL);
    memset(str, 0, 4096);

    while (rax > read)
    {
        if ((int)(read + sizeof(tmp)) > allocated)
        {
            allocated *= 2;
            if (!(str = realloc(str, allocated)))
                return (NULL);
        }
        tmp = ptrace(PTRACE_PEEKDATA, child, addr + read);
        if (errno != 0)
        {
            str[read] = 0;
            break ;
        }
        memcpy(str + read, &tmp, sizeof(tmp));
        read += sizeof(tmp);
    }
    return (str);
}

int     handle_str(pid_t child, t_print *pr, unsigned long long int reg)
{
    char    *s;
    int     len;

    len = 0;
    s = NULL;
    if (pr->syscall == 0 || pr->syscall == 1 || pr->syscall == 17)
    {
        s = read_chars(child, reg, pr->regs.rax);
        write_str(s, pr->regs.rax);
    }
    else
    {
        s = read_string(child, reg, &len);
        dprintf(2, "\"%s\"", s);
    }
    if (s)
        free(s);
    s = NULL;
    return (1);
}