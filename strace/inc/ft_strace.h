#ifndef SYSCALLS_LOOP_H
# define SYSCALLS_LOOP_H

#include <sys/user.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
#include <sys/ptrace.h>
#include <sys/reg.h>
#include <sys/wait.h>
#include <linux/unistd.h>
#include <errno.h>
#include <ctype.h>
#include <sys/stat.h>
#include <assert.h>


typedef struct  s_print
{
    long        syscall;
    long        ret_sys;
    struct user_regs_struct     regs;
    int                         flag;
    void                        *env_addr;
    unsigned int                env_count;
    char                        *target;
    char                        **args;
}               t_print;


int                     do_trace(pid_t pid, t_print *print);

int                     handle_str(pid_t child, t_print *pr, unsigned long long int reg);
void                    handle_execve(pid_t child, t_print *print);
char                    *read_string(pid_t child, unsigned long addr, int *len);

unsigned long long int  get_syscall_arg(pid_t child, int which);

int                     handle_sig(pid_t pid, int status);
void                    sig_block(void);
void                    sig_empty(void);



#endif
