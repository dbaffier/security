#include "ft_strace.h"
#include "syscalls_64.h"

int handle_sig(pid_t pid, int status)
{
	siginfo_t		siginfo;

	ptrace(PTRACE_GETSIGINFO, pid, 0, &siginfo);
	if (WSTOPSIG(status) > 0 && WSTOPSIG(status) < 32)
	{
		if (WSTOPSIG(status) == SIGSEGV)
		{
			dprintf(2, "--- %s {si_signo=%s, si_code=%d, si_addr=%p} ---\n", sys_sig64[siginfo.si_signo].str,
					sys_sig64[siginfo.si_signo].str, siginfo.si_code, siginfo.si_addr);
			dprintf(2, "+++ killed by %s ---\n", sys_sig64[siginfo.si_signo].str);
			dprintf(2, "Segmentation fault\n");
			exit(128 + WSTOPSIG(status));
		}
		else if (WSTOPSIG(status) == SIGCHLD)
		{
			dprintf(2, "--- %s {si_signo=%s, si_code=%d, si_pid=%d, si_uid=%d, si_status=%d"
				", si_utime=%ld, si_stime=%ld} ---\n", sys_sig64[siginfo.si_signo].str,
				sys_sig64[siginfo.si_signo].str, siginfo.si_code, siginfo.si_pid, siginfo.si_uid,
				siginfo.si_status, siginfo.si_utime, siginfo.si_stime);
		}
		else
		{
			dprintf(2, "--- %s {si_signo=%s, si_code=%d, si_pid=%d, si_uid=%d} ---\n",
				sys_sig64[siginfo.si_signo].str,
				sys_sig64[siginfo.si_signo].str,
				siginfo.si_code,
				siginfo.si_pid,
				siginfo.si_uid
			);
		}
	}
	return 0;
}

void	sig_block(void)
{
	sigset_t	block;

	if (sigemptyset(&block) ||
		sigaddset(&block, SIGHUP) ||
		sigaddset(&block, SIGINT) ||
		sigaddset(&block, SIGQUIT) ||
		sigaddset(&block, SIGPIPE) ||
		sigaddset(&block, SIGTERM) ||
		sigprocmask(SIG_BLOCK, &block, NULL)
	)
	{
		exit(1);
	}
}

void	sig_empty(void)
{
	sigset_t	set;

	if (sigemptyset(&set) || sigprocmask(SIG_SETMASK, &set, NULL))
		exit(1);
}
