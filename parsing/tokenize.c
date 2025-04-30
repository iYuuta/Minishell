#include "../minishell.h"

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
		write(2, ": Is a directory", 16);
		return ;
	}
	else
	{
		return_value(126, 1);
		write(2, "minishell: ", 11);
		write(2, str, ft_strlen(str));
		write(2, ": Not a directory", 17);
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

int	identify_tokens(t_arg *token)
{
	if (token && check_first_arg(token->token))
		return (1);
	while (token)
	{
		if (!ft_strcmp(token->token, "||") || !ft_strcmp(token->token, "&&"))
			return (print_error(token->token, 1), 1);
		if (is_redirection(token->token))
		{
			token->type = is_redirection(token->token);
			if (!token->next)
				return (print_error("new line", 1), 1);
			if (is_redirection(token->next->token))
				return (print_error(token->next->token, 1), 1);
			token = handle_redir(token);
			if (!token)
				break ;
		}
		else
			token->type = is_pipe(token->token);
		if (token->type == PIPE && (!token->next
				|| !ft_strcmp(token->next->token, "|")))
			return (print_error(token->token, 1), 1);
		token = token->next;
	}
	return (0);
}

t_arg	*tokenize_arg(char **av, t_env *env)
{
	int		i;
	t_arg	*head;
	t_arg	*tmp;

	i = -1;
	head = NULL;
	while (av[++i])
	{
		tmp = ft_lstnew(av[i]);
		tmp->env = env;
		ft_lstadd_back(&head, tmp);
	}
	if (identify_tokens(head))
		return (NULL);
	return (head);
}
