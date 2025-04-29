#include "minishell.h"

void copy_attributes(int flag)
{
	static struct termios	term_attr;

	if (flag)
	{
		if (tcgetattr(0, &term_attr) == -1)
		{
			ft_putstr_fd("failed to copy the current attributes of the terminal\n", 2);
			exit(1);
		}
	}
	else
	{
		if (tcsetattr(0, TCSANOW, &term_attr) == -1)
		{
			ft_putstr_fd("failed to restore the old attributes of the terminal\n", 2);
			exit(1);
		}
	}
}

int	read_shell(t_env *env, char *head_line)
{
	char	*str;

	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, handle_signales);
	while (1)
	{
		str = readline(head_line);
		if (!str)
		{
			env_malloc(0, 0);
			ft_putendl_fd("exit", 2);
			exit(0);
		}
		if (*str)
		{
			add_history(str);
			execution(str, env);
		}
		free(str);
		ft_malloc(0, 0);
	}
}

int	main(int ac, char **av, char **env)
{
	t_env	*envirement;

	if (ac > 1)
		return (1);
	(void)av;
	if (!isatty(0) || !isatty(1) || !isatty(2))
		return (ft_putendl_fd("insecure source", 2), 1);
	copy_attributes(1);
	oldenv(env);
	store_pwd(NULL);
	envirement = env_init(env, NULL, 0);
	if (read_shell(envirement, "minishell>> ") == 1)
		return (1);
	return (0);
}
