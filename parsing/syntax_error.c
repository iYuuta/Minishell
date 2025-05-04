#include "../minishell.h"

static void	print_error(char *str, int flag)
{
	if (flag == 1)
	{
		return_value(2, 1);
		write(2, "minishell: syntax error near unexpected token `", 47);
		write(2, str, ft_strlen(str));
	}
	else if (flag == 0)
	{
		return_value(126, 1);
		write(2, "minishell: ", 11);
		write(2, str, ft_strlen(str));
		write(2, ": Is a directory\n", 17);
		return ;
	}
	else
	{
		return_value(126, 1);
		write(2, "minishell: ", 11);
		write(2, str, ft_strlen(str));
		write(2, ": Not a directory\n", 18);
		return ;
	}
	write(2, "\n", 2);
}

int	check_first_arg(char *str)
{
	struct stat	info;

	if (!ft_strcmp(str, "|"))
		return (print_error(str, 1), 1);
	if (ft_strchr(str, '/') && access(str, F_OK) == 0
		&& stat(str, &info) == -1)
		return (print_error(str, 2), 1);
	if (ft_strchr(str, '/') && S_ISDIR(info.st_mode))
		return (print_error(str, 0), 1);
	return (0);
}

t_arg	*handle_redir(t_arg *token)
{
	token = token->next;
	if (token && !ft_strcmp(token->token, "|"))
	{
		token->type = PIPE;
		return (token);
	}
	else if (token)
		token->type = file;
	return (token);
}

int	check_error(t_arg *arg)
{
	if (arg && check_first_arg(arg->token))
		return (1);
	while (arg)
	{
		if (!ft_strcmp(arg->token, "||") || !ft_strcmp(arg->token, "&&"))
			return (1);
		if (is_redirection(arg->token))
		{
			if (!arg->next)
				return (print_error("new line", 1), 1);
			if (is_redirection(arg->next->token))
				return (print_error(arg->next->token, 1), 1);
			arg = handle_redir(arg);
			if (!arg)
				break ;
		}
		if (is_pipe(arg->token) && !arg->next)
			return (1);
		arg = arg->next;
	}
	return (0);
}

int	syntax_error(char *str, t_env *env)
{
	t_arg	*head;

	head = split_args(str, env);
	if (check_error(head))
		return (return_value(2, 1), 1);
	return (0);
}
