#include "syscalls_64.h"
#include "ft_strace.h"

#ifdef __amd64__
#define eax rax
#define orig_eax orig_rax
#else
#endif

#define offsetof(a, b) __builtin_offsetof(a,b)
#define get_reg(child, name) __get_reg(child, offsetof(struct user, regs.name))

unsigned long long int __get_reg(pid_t child, int off)
{
    unsigned long long int val = ptrace(PTRACE_PEEKUSER, child, off);
    assert(errno == 0);
    return val;
}

unsigned long long int get_syscall_arg(pid_t child, int which)
{
    switch (which)
    {
#ifdef __amd64__
    case 0: return get_reg(child, rdi);
    case 1: return get_reg(child, rsi);
    case 2: return get_reg(child, rdx);
    case 3: return get_reg(child, r10);
    case 4: return get_reg(child, r8);
    case 5: return get_reg(child, r9);
#else
    case 0: return get_reg(child, ebx);
    case 1: return get_reg(child, ecx);
    case 2: return get_reg(child, edx);
    case 3: return get_reg(child, esi);
    case 4: return get_reg(child, edi);
    case 5: return get_reg(child, ebp);
#endif
    default: return -1L;
    }
}

void    handle_args(pid_t child, t_print *pr)
{
    int     n;
    unsigned long long int    reg;
    int     type;

    n = 0;
    if (pr->syscall == 59)
    {
        handle_execve(child, pr);
        n = 10;
    }
    while (n < systab64[pr->syscall].nargs)
    {
        type = systab64[pr->syscall].args[n];
        reg = get_syscall_arg(child, n);
        switch (type)
        {
            case E_INT:
                dprintf(2, "%d", (int)reg);
                break ;
            case E_UINT:
                dprintf(2, "%u", (unsigned int)reg);
                break ;
            case E_PTR:
                dprintf(2, "%#llx", (unsigned long long int)reg);
                break ;
            case E_STR:
                handle_str(child, pr, reg);
                break ;
            case E_STRUCT:
                reg != 0 ? dprintf(2, "{ %#x }", (unsigned int)reg) : dprintf(2, "NULL");
                break ;
            default:
                dprintf(2, "NULL");
                break ;
        }
        if (n < systab64[pr->syscall].nargs - 1)
            dprintf(2, ", ");
        n++;
    }
    dprintf(2, ") = ");

}

static int handle_syscall(pid_t pid, t_print *print)
{
	ptrace(PTRACE_GETREGS, pid, 0, &print->regs);
	print->syscall = print->regs.orig_rax;
	print->ret_sys = print->regs.rax;
	return 0;
}

int wait_for_syscall(pid_t child, int skip)
{
    int     status;

    while (1)
    {
        ptrace(PTRACE_SYSCALL, child, 0, 0);
        sig_empty();
        waitpid(child, &status, 0);
        sig_block();
        if (skip && WIFSTOPPED(status) && WSTOPSIG(status) & (SIGTRAP | 0x80))
            return (0);
        else if (!skip && WIFSTOPPED(status) && WSTOPSIG(status) & 0x80)
            return (0);
        else
        {
            if (WIFEXITED(status))
            {
                dprintf(2, "+++ exited with %d +++\n", WEXITSTATUS(status));
                exit(0);
            }
            else
				handle_sig(child, status);
        }

    }
	return (0);
}

void    sys_err_print(t_print *print)
{
    int     type;

    type = 0;
    if (print->ret_sys >= 0)
    {
        type = systab64[print->syscall].sys_ret;
        if (type == E_NOT)
            ;
        else if (type == E_INT)
            dprintf(2, "%d", (int)print->ret_sys);
        else if (type ==  E_UINT)
            dprintf(2, "%u", (unsigned int)print->ret_sys);
        else if (type == E_PTR)
            dprintf(2, "%#llx", (unsigned long long int)print->ret_sys);
    }
    else
    {
        if (-print->ret_sys != ENOSYS && -print->ret_sys < 132)
        {
            dprintf(2, "%d ", -1);
            dprintf(2, "%s (%s)", sys_err64[-print->ret_sys].str, sys_err64[-print->ret_sys].msg);
        }
        else
            dprintf(2, "?");
    }
    dprintf(2, "\n");
}

int		do_trace(pid_t pid, t_print *print)
{
	int				i = 0;

	if (ptrace(PTRACE_SEIZE, pid, 0, PTRACE_O_TRACESYSGOOD) < 0 
        || ptrace(PTRACE_INTERRUPT, pid, 0, 0) < 0)
		exit(0);
	sig_empty();
	waitpid(pid, NULL, 0);
	sig_block();
	while (1)
	{
		wait_for_syscall(pid, 1);
		handle_syscall(pid, print);

		if ((i == 0 && print->syscall == 59) || i)
        {
            i = 1;
            dprintf(2, "%s(", systab64[print->syscall].name);
            handle_args(pid, print);
            sys_err_print(print);
        }
		ptrace(PTRACE_SEIZE, pid, 0L, PTRACE_O_TRACESYSGOOD);
		wait_for_syscall(pid, 0);
		handle_syscall(pid, print);
		if ((i == 0 && print->syscall == 59) || i)
        {
			i = 1;
            if (print->syscall == 231)
            {
                dprintf(2, "%s(", systab64[print->syscall].name);
                handle_args(pid, print);
                sys_err_print(print);
            }
		}
	}
	return (0);
}
