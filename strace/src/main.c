#define _GNU_SOURCE
#include "ft_strace.h"

int		check_access(char *path)
{
	struct stat	buf;

	if (!path)
		return (0);
	if (access(path, F_OK))
		return (0);
	if (access(path, X_OK))
		return (0);
	if (stat(path, &buf))
		return (0);
	if (S_ISDIR(buf.st_mode))
		return (0);
	if (buf.st_mode & S_IXUSR)
		return (1);
	return (0);
}

void	do_env(int ac, char **av, char **env, t_print *print)
{
	char	*path;
	char	*token;
	char	*bin;
	int		i;

	(void)ac;
	path = NULL;
	bin = NULL;
	print->flag = 1;
	if (env)
	{
		for (i = 0; env[i]; i++)
		{
			if (strncmp(env[i], "PATH=", 5) == 0)
				path = env[i] + 5;
		}
	}
	print->env_count = i;
	print->env_addr = &env;
	if (strchr(av[0], '/') == NULL && path)
	{
		while ((token = strsep(&path, ":")) != NULL)
		{
			bin = malloc(strlen(av[0]) + strlen(token) + 2);
			bzero(bin, strlen(av[0]) + strlen(token) + 2);
			strcat(bin, token);
			strcat(bin, "/");
			strcat(bin, av[0]);
			if (check_access(bin))
			{
				print->target = bin;
				break ;
			}
			free(bin);
		}
	}
	else
	{
		if (check_access(av[0]))
			print->target = strdup(av[0]);
	}
	if (print->target == NULL)
	{
		dprintf(2, "ft_strace: No such file of directory : %s\n", av[0]);
		exit(1);
	}
	print->args = av;
}

int		main(int ac, char **av, char **env)
{
	t_print	print;
	pid_t	pid;

	memset(&print, 0, sizeof(struct s_print));
	do_env(ac - 1, av + 1, env, &print);
	pid = fork();
	if (pid == 0)
	{
		kill(getpid(), SIGSTOP);
		if (execve(print.target, print.args, env) < 0) {
			exit(1);
		}
	}
	else if (pid > 0)
	{
		do_trace(pid, &print);
	}
	return (0);
}
