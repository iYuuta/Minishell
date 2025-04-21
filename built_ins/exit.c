#include "../minishell.h"

static void print_error(char *str)
{
	ft_putstr_fd("bash: exit:", 2);
	ft_putstr_fd(str, 2);
	ft_putendl_fd(": numeric argument required", 2);
}

int is_exit_valid(char *str)
{
	while (str)
	{
		if (!ft_isdigit(*str))
			return (1);
		str++;
	}
	return (0);
}

int	exit_shell(t_arg *arg)
{
	ft_putendl_fd("exit", 2);
	if (arg->next)
	{
		if (is_exit_valid(arg->next->token))
			print_error(arg->next->token);
	}
	ft_malloc(0, 0);
	env_malloc(0, 0);
	return (69);
}