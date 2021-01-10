#ifndef SYSCALLS_TABLE_H
# define SYSCALLS_TABLE_H

enum e_args {
	E_NOT = 0,
	E_INT = 1,
	E_UINT = 2,
	E_PTR = 3,
	E_STR = 4,
	E_STRUCT = 5
};

typedef struct		s_syscall
{
	char				*name;
	int					nargs;
	enum e_args			args[6];
	int					sys_ret;
}					t_syscall;

typedef struct		s_syserr
{
	int					code;
	char				*str;
	char				*msg;
}					t_syserr;

typedef struct		s_sigerr
{
	int					code;
	char				*str;
}					t_sigerr;

extern const t_syscall	systab64[];
extern const t_syserr	sys_err64[];
extern const t_sigerr	sys_sig64[];

#endif
