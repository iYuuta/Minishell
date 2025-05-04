#include "../minishell.h"

long	custom_atoi(const char *str)
{
	int		i;
	int		sign;
	long	result;

	i = 0;
	sign = 1;
	result = 0;
	if (str[i] && (str[i] == '-' || str[i] == '+'))
	{
		if (str[i] == '-')
			sign = -sign;
		i++;
	}
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		if (result > (9223372036854775807 - (str[i] - 48)) / 10)
			return (69);
		result = (result * 10) + (str[i] - 48);
		i++;
	}
	return (result * sign);
}

static void	print_error(char *str, int flag)
{
	ft_putstr_fd("minishell: exit:", 2);
	ft_putstr_fd(str, 2);
	if (flag)
		ft_putendl_fd(": numeric argument required", 2);
	else
		write(2, "\n", 1);
}

int	is_exit_valid(char *str)
{
	if (*str && (*str == '-' || *str == '+'))
		str++;
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (1);
		str++;
	}
	return (0);
}

void	free_mem(int status)
{
	ft_malloc(0, 0);
	env_malloc(0, 0);
	exit(status);
}

int	exit_shell(t_cmd *cmd)
{
	long	exit_status;

	exit_status = return_value(0, 0);
	if (!cmd->next && cmd->number == 1)
		ft_putendl_fd("exit", 1);
	else
		return_value(0, 1);
	if (cmd->tokens->next)
	{
		exit_status = custom_atoi(cmd->tokens->next->token);
		if (is_exit_valid(cmd->tokens->next->token)
			|| (exit_status == 69 && ft_strcmp("69", cmd->tokens->next->token)))
		{
			print_error(cmd->tokens->next->token, 1);
			free_mem(255);
		}
		if (exit_status > 255 || exit_status < 0)
			exit_status = exit_status % 256;
	}
	if (cmd->tokens->next && cmd->tokens->next->next)
		return (print_error(" too many argments", 0), 1);
	else
		return (ft_malloc(0, 0), env_malloc(0, 0), free_mem(exit_status), 0);
	return (0);
}
